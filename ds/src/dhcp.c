/*****************************************************
 * dhcp                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 4.08.2022                                   *
 *****************************************************/

/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "dhcp.h" 
#include "trie.h"

#define BYTES_IN_IP 4
#define UNUSED(param)  (void)param

static const size_t g_max_subnest_size = 32;
static const size_t g_num_of_children = 2;
static const size_t g_pre_alloc_net_size = 1;

typedef enum 
{
	GO_LEFT,
	GO_RIGHT,
	NUM_OF_CHILDRENS
}child_ty; /* TODO: child_param*/

struct dhcp
{
	trie_ty *trie;
	size_t subnet_size;
	size_t host_ip_len;
	const unsigned char *subnet_ip;
};
static const size_t g_dhcp_ty_size = sizeof(dhcp_ty);


static size_t DHCPGetHostIpLen(dhcp_ty *dhcp);
/* util function for create */
static status_ty DhcpInitialize(dhcp_ty *dhcp, const unsigned char *subnet_ip,
                               size_t subnet_size);
static return_status_ty DhcpPreAllocNetAndCommunication(dhcp_ty *dhcp);
/* util function for alloc */
static status_ty AllocateIp(dhcp_ty *dhcp, unsigned int requested_ip,
									unsigned int *o_ip_address);
static void AssignFullFlagsInPath(trie_iterator_ty position,
                                 unsigned int path_to_set, 
								 size_t host_ip_size);
static unsigned int DHCPGetNextBit(unsigned int num, size_t shift_size);
static unsigned int ConvertIpCharToInt(const unsigned char *ip_address);
static unsigned int AddIpByOne(unsigned int *ip);
static bool_ty IsBothChildOccupied(trie_iterator_ty position);
static return_status_ty IsIpMatchRequest(unsigned int requested_ip,
                                         unsigned int result_ip);
static unsigned int UsIntMirror(unsigned int us_int_num);
static void ConvertIpIntToChar(unsigned int ip_address,
                                 unsigned char *o_user_ip);
static void ByteMirror(unsigned char *ch);
static unsigned int GetUnsignedInt(const unsigned char *ip);
/* util function for free */
static trie_iterator_ty DhcpFindIpPath(dhcp_ty *dhcp, unsigned int requested_ip,
									unsigned int *o_ip_address);
static void DeAttachParentFromChild(dhcp_ty *dhcp, size_t index,
                trie_iterator_ty parent,trie_iterator_ty child);
static return_status_ty DhcpFreeIpPath(dhcp_ty *dhcp, unsigned int ip_to_free);
static void FreeLeafs(trie_iterator_ty child, trie_iterator_ty parent,
                         size_t index);


dhcp_ty *DHCPCreate(const unsigned char *subnet_ip, size_t subnet_size)
{
	dhcp_ty *dhcp = NULL;

	assert(NULL != subnet_ip);

	dhcp = (dhcp_ty *)malloc(g_dhcp_ty_size);
	if (NULL == dhcp)
	{
		return NULL;	
	}
	
	if (MALLOC_FAILURE == DhcpInitialize(dhcp,subnet_ip, subnet_size))
	{
		free(dhcp);
		dhcp = NULL;
		return NULL;
	}
	
	return (dhcp);
}

void DHCPDestroy(dhcp_ty *dhcp)
{
	assert(NULL != dhcp);

	TrieDestroy(dhcp->trie);
	
	free(dhcp);
	dhcp = NULL;
}

return_status_ty DHCPAllocateIp(dhcp_ty *dhcp,
                               unsigned char *o_ip_address, 
                               const unsigned char *requested_ip_address) 
{
	status_ty allocation_status = SUCCESS;
	unsigned int o_int_ip_address = 0;
	unsigned int int_requested_ip_address = 0;

    assert(NULL != dhcp);
    assert(NULL != requested_ip_address);
    assert(NULL != o_ip_address);

	/* takes the whole chunk of address as char ptr
	  and converts it to unsigned int  block in memory */
	int_requested_ip_address = ConvertIpCharToInt(requested_ip_address);

	allocation_status = AllocateIp(dhcp, int_requested_ip_address,
	                                    &o_int_ip_address);
	if (MALLOC_FAILURE == allocation_status)
	{
		return FAILED_TO_ALLOCATE;
	}

	ConvertIpIntToChar(o_int_ip_address, o_ip_address);

	return (IsIpMatchRequest(int_requested_ip_address, o_int_ip_address));
}

return_status_ty DHCPFreeIp(dhcp_ty *dhcp, const unsigned char *ip_to_free) 
{
	assert(NULL != ip_to_free);
	assert(NULL != dhcp);	

	return (DhcpFreeIpPath(dhcp, ConvertIpCharToInt(ip_to_free))); 
}
size_t DHCPCountFree(const dhcp_ty *dhcp)
{
	size_t ip_counter = 0;

	assert (NULL != dhcp);
	/* to use field from the struct */ 
	ip_counter = TrieCountLeafs(dhcp->trie, g_num_of_children);
	ip_counter += g_pre_alloc_net_size;

	return ((1 << dhcp->host_ip_len) - ip_counter);
}
/********************************STATIC FUNCTION*******************************/

static status_ty DhcpInitialize(dhcp_ty *dhcp, const unsigned char *subnet_ip,
                               size_t subnet_size)
{
	dhcp->trie = TrieCreate(g_num_of_children);
	if (NULL == dhcp->trie)
	{
		return MALLOC_FAILURE;
	}
	
	dhcp->subnet_size = subnet_size;
	dhcp->subnet_ip = subnet_ip;
	dhcp->host_ip_len = g_max_subnest_size - subnet_size;


	if (ALLOCATED_REQUSTED_ADDRESS != DhcpPreAllocNetAndCommunication(dhcp))
	{
		DHCPDestroy(dhcp);
		return MALLOC_FAILURE;
	}

	return SUCCESS;
}

static return_status_ty DhcpPreAllocNetAndCommunication(dhcp_ty *dhcp)
{
	/* to fix address name */
	unsigned char ip_address[BYTES_IN_IP] = {0};
	unsigned char ip_address1[BYTES_IN_IP] = {0};
	unsigned char ip_address2[BYTES_IN_IP] = {0};
	unsigned char broad_cast_bit = 0;
	unsigned char end_mark_bit = 0;
	
	/* better naming - broadcast and etc */
	unsigned int last_bit_add = ConvertIpCharToInt(dhcp->subnet_ip) + 
	                            (1 << DHCPGetHostIpLen(dhcp));

	unsigned int bit_add = ConvertIpCharToInt(dhcp->subnet_ip) + 
	                       (1 << DHCPGetHostIpLen(dhcp)) - 1;
	
	ConvertIpIntToChar(bit_add, &broad_cast_bit);
	ConvertIpIntToChar(last_bit_add, &end_mark_bit);
	
	if (ALLOCATED_REQUSTED_ADDRESS !=
	   DHCPAllocateIp(dhcp, ip_address, dhcp->subnet_ip))
	{
		return FAILED_TO_ALLOCATE;
	}
	

	if (ALLOCATED_REQUSTED_ADDRESS !=
	   DHCPAllocateIp(dhcp, ip_address1, &broad_cast_bit))
	{
		return FAILED_TO_ALLOCATE;
	}
	
	if (ALLOCATED_REQUSTED_ADDRESS !=
	   DHCPAllocateIp(dhcp, ip_address2, &end_mark_bit))
	{
		return FAILED_TO_ALLOCATE;
	}

	return (ALLOCATED_REQUSTED_ADDRESS);
}


static size_t DHCPGetHostIpLen(dhcp_ty *dhcp)
{
	assert (NULL != dhcp);

	return (dhcp->host_ip_len);
}

static unsigned int ConvertIpCharToInt(const unsigned char *ip_address)
{
	return (UsIntMirror(GetUnsignedInt(ip_address)));
}

static void ConvertIpIntToChar(unsigned int ip_address,
                                 unsigned char *o_user_ip)
{
	*(unsigned int *)o_user_ip = UsIntMirror(ip_address);
	
}

static unsigned int GetUnsignedInt(const unsigned char *ip)
{
	return(*(unsigned int *)(ip));
}
static return_status_ty IsIpMatchRequest(unsigned int requested_ip,
                                         unsigned int result_ip)
{
	return (requested_ip == result_ip ? ALLOCATED_REQUSTED_ADDRESS :
	                                    ALLOCATED_AVAILABLE_ADDRESS);
}


static unsigned int UsIntMirror(unsigned int us_int_num)
{
	us_int_num = ((us_int_num >> 1) & 0x55555555) |
	             ((us_int_num << 1) & 0xAAAAAAAA);

    us_int_num = ((us_int_num >> 2) & 0x33333333) |
	             ((us_int_num << 2) & 0xCCCCCCCC);

    us_int_num = ((us_int_num >> 4) & 0x0F0F0F0F) |
	             ((us_int_num << 4) & 0xF0F0F0F0);

    us_int_num = ((us_int_num >> 8) & 0x00FF00FF) |
	             ((us_int_num << 8) & 0xFF00FF00);
    us_int_num = ((us_int_num >> 16) & 0x0000FFFF) |
	             ((us_int_num << 16) & 0xFFFF0000);

    return us_int_num;
}

static void ByteMirror(unsigned char *ch)
{
	*ch = ((*ch >> 1) & 0x55555555) |
		((*ch << 1) & 0xAAAAAAAA);

    *ch = ((*ch >> 2) & 0x33333333) |
		((*ch << 2) & 0xCCCCCCCC);

    *ch = ((*ch >> 4) & 0x0F0F0F0F) |
		((*ch << 4) & 0xF0F0F0F0);

}
static unsigned int AddIpByOne(unsigned int *ip)
{
	size_t byte_size = 4;
	size_t i = 0;
	unsigned char *ip_char = (unsigned char *)ip;
	for (	; i < byte_size; ++i)
	{
		ByteMirror(ip_char + i);
	}
	*ip = -(~*ip);
	
	ip_char = (unsigned char *)ip;
	for (i = 0 ; i < byte_size; ++i)
	{
		ByteMirror(ip_char + i);
	}
	return *ip;
}
static status_ty AllocateIp(dhcp_ty *dhcp,
                            unsigned int requested_ip,
							unsigned int *o_ip_address)
{
	trie_iterator_ty ip_beginning = NULL;

	assert(NULL != dhcp->trie);
	assert(NULL != o_ip_address);
	assert(NULL != dhcp);
	
	ip_beginning = TrieBegin(dhcp->trie);

	ip_beginning = DhcpFindIpPath(dhcp, requested_ip, o_ip_address);
	if (NULL == ip_beginning)
	{
		return (MALLOC_FAILURE);
	}

	AssignFullFlagsInPath(TrieBegin(dhcp->trie),
	                     requested_ip,
	                     DHCPGetHostIpLen(dhcp));
	
	return SUCCESS;
}

static trie_iterator_ty DhcpFindIpPath(dhcp_ty *dhcp,
                                       unsigned int requested_ip,
									   unsigned int *o_ip_address)
{
	size_t i =0;
	trie_iterator_ty parent = NULL;
	trie_iterator_ty children = NULL;
	trie_ty *dhcp_trie = NULL;

	assert(NULL != dhcp->trie);
	assert(NULL != o_ip_address);
	assert(NULL != dhcp);

	dhcp_trie = dhcp->trie;
	parent = TrieBegin(dhcp_trie);

	for ( ; i < DHCPGetHostIpLen(dhcp) ; ++i)
	{
		unsigned int next_ip_bit = DHCPGetNextBit(requested_ip, i);

		children = TrieIterGetChildrenByIndex(parent, next_ip_bit);
		if (NULL == children)
		{
			parent = TrieInsert(dhcp_trie, parent, next_ip_bit);
			if (NULL == parent)
			{
				return (NULL);
			}
		}
		else if (PathIsFull(children))
		{
			unsigned int new_ip_to_search = AddIpByOne(&requested_ip);
			return (DhcpFindIpPath(dhcp, new_ip_to_search, o_ip_address));
		}
		else
		{
			parent = children;
		}
	}

	TrieSetIsFullOnPath(parent);
	*o_ip_address = requested_ip;
	
	return (parent);
}

static bool_ty IsBothChildOccupied(trie_iterator_ty position)
{
	trie_iterator_ty zero_bit_arch = NULL;
	trie_iterator_ty one_bit_arch = NULL;

	assert (NULL != position);	

	zero_bit_arch = TrieIterGetChildrenByIndex(position, GO_LEFT);
	one_bit_arch = TrieIterGetChildrenByIndex(position, GO_RIGHT);

	if ( NULL == zero_bit_arch || !PathIsFull(zero_bit_arch))
	{
		return FALSE;
	}
	else if ( NULL == one_bit_arch || !PathIsFull(one_bit_arch))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

static return_status_ty DhcpFreeIpPath(dhcp_ty *dhcp, unsigned int ip_to_free)
{
	size_t i =0;
	trie_iterator_ty parent = NULL;
	trie_iterator_ty children = NULL;
	trie_ty *dhcp_trie = NULL;
	unsigned int next_ip_bit = 0;

	assert(NULL != dhcp->trie);
	assert(NULL != dhcp);

	dhcp_trie = dhcp->trie;
	parent = TrieBegin(dhcp_trie);

	for ( ; i < DHCPGetHostIpLen(dhcp) ; ++i , parent = children)
	{
		next_ip_bit = DHCPGetNextBit(ip_to_free, i);

		children = TrieIterGetChildrenByIndex(parent, next_ip_bit);
		if (NULL == children)
		{
			return (DOUBLE_FREE);
		}
		
		DeAttachParentFromChild(dhcp, i,parent, children); 
	}

	FreeLeafs(children, parent, next_ip_bit);

	return (FREE_SUCCESFULL);
}

static void DeAttachParentFromChild(dhcp_ty *dhcp, size_t index,
                                   trie_iterator_ty parent,
                                   trie_iterator_ty child)
{
	UNUSED(parent);

	if ( index == DHCPGetHostIpLen(dhcp) -1)
	{
		parent = NULL;
	}

	TrieUnsetIsFullOnPath(child);
}
static void FreeLeafs(trie_iterator_ty child, trie_iterator_ty parent,
                         size_t index)
{
	parent->parent->children[index] = NULL;
	free(child);
	child = NULL;
}
static void AssignFullFlagsInPath(trie_iterator_ty position,
                                 unsigned int path_to_set, 
								 size_t host_ip_size)
{
	size_t i = 0;

	for ( ; i < host_ip_size ; ++i )
	{
		unsigned int next_ip_bit = DHCPGetNextBit(path_to_set, i);

		if (IsBothChildOccupied(position))
		{
			TrieSetIsFullOnPath(position);
			return;
		}
		
		position = TrieIterGetChildrenByIndex(position, next_ip_bit);
	}
}

static unsigned int DHCPGetNextBit(unsigned int num, size_t shift_size)
{
	unsigned char mask = 1;
	return ((num >> shift_size) & mask);
}