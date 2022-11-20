/*****************************************************
 * dhcp_test                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 04.08.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* stdlib */
#include <limits.h> /* CHAR_BIT */

#include "dhcp.h"
static const size_t g_max_subnest_size = 32;
static const size_t g_intialize_alloc_size = 3;
static void CreateTest(void);
static void AllocTest(void);
static void CountAndFreeTest(void);
static void CountWeirdTest(void);
static void SubnetZeroTest(void);
int main(void)
{
	CreateTest();
	AllocTest();	
	CountAndFreeTest();
	CountWeirdTest();
	SubnetZeroTest(); 
	return (0);
}

static void CreateTest(void)
{
	unsigned char subnet_ip[] = {123, 1, 2, 0};
	size_t subnet_size = 8;

	dhcp_ty *dhcp = DHCPCreate(subnet_ip, subnet_size);
	DHCPDestroy(dhcp);
}

static void AllocTest(void)
{
	unsigned char subnet_ip[] = { 123, 001, 002 , 000};
	unsigned char ip_address[4] = {0}; 
	unsigned char ip_address1[4] = {0};
	unsigned char ip_address2[4] = {0}; 
	unsigned char requested_ip_address [] = { 123, 001, 002, 001};
	unsigned char requested_ip_address1 [] = { 123, 001, 002, 001};
	unsigned char requested_ip_address2 [] = { 123, 001, 002, 003};
	size_t subnet_size = 24;	
	dhcp_ty *dhcp = DHCPCreate(subnet_ip, subnet_size);
	assert(ALLOCATED_REQUSTED_ADDRESS == 
	DHCPAllocateIp(dhcp, ip_address , requested_ip_address));
	
	assert(ALLOCATED_AVAILABLE_ADDRESS == 
	DHCPAllocateIp(dhcp, ip_address1 , requested_ip_address1));
	
	assert(ALLOCATED_REQUSTED_ADDRESS ==
	DHCPAllocateIp(dhcp, ip_address2 , requested_ip_address2));
	printf("%d.%d.%d.%d \n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
	printf("%d.%d.%d.%d \n", ip_address1[0], ip_address1[1], ip_address1[2], ip_address1[3]);
	printf("%d.%d.%d.%d \n", ip_address2[0], ip_address2[1], ip_address2[2], ip_address2[3]);
	assert (FREE_SUCCESFULL ==  DHCPFreeIp(dhcp, ip_address2));
	DHCPDestroy(dhcp);	
}

static void CountAndFreeTest(void)
{
	unsigned char subnet_ip[] = { 123, 001, 002 , 000};
	unsigned char ip_address[4] = {0}; 
	unsigned char ip_address1[4] = {0};
	unsigned char ip_address2[4] = {0}; 
	unsigned char requested_ip_address [] = { 123, 001, 002, 001};
	unsigned char requested_ip_address1 [] = { 123, 001, 002, 001};
	unsigned char requested_ip_address2 [] = { 123, 001, 002, 003};
	size_t subnet_size1 = 24;
	size_t host_size = g_max_subnest_size - subnet_size1;
	size_t ip_var_left = (1 << host_size);
	dhcp_ty *dhcp = DHCPCreate(subnet_ip, subnet_size1);
	
	ip_var_left -= g_intialize_alloc_size;
	
	DHCPAllocateIp(dhcp, ip_address , requested_ip_address);
	DHCPAllocateIp(dhcp, ip_address1 , requested_ip_address1);
	DHCPAllocateIp(dhcp, ip_address2 , requested_ip_address2);
	puts("starting count and free test:");
	ip_var_left -= 3;
	assert (ip_var_left == DHCPCountFree(dhcp));
	puts("maximum ip_address");
	while (ip_var_left != 1)
	{
		assert(ALLOCATED_AVAILABLE_ADDRESS == 
		DHCPAllocateIp(dhcp, ip_address , requested_ip_address));
		--ip_var_left;
	}
	printf("%d.%d.%d.%d \n",
	        ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
	assert(1 == DHCPCountFree(dhcp));
	assert (FREE_SUCCESFULL ==  DHCPFreeIp(dhcp, ip_address));
	assert (FREE_SUCCESFULL ==  DHCPFreeIp(dhcp, ip_address1));
	assert(3 == DHCPCountFree(dhcp));
	/* trying to double free */
	assert (DOUBLE_FREE ==  DHCPFreeIp(dhcp, ip_address1));
	DHCPDestroy(dhcp);
}

static void CountWeirdTest(void)
{
	unsigned char subnet_ip[] = { 111, 110, 122 , 000};
	unsigned char ip_address[4] = {0}; 
	unsigned char ip_address1[4] = {0};
	unsigned char ip_address2[4] = {0}; 
	unsigned char requested_ip_address [] = { 111, 110, 122, 001};
	unsigned char requested_ip_address1 [] = { 111, 110, 122, 001};
	unsigned char requested_ip_address2 [] = { 111, 110, 122, 003};
	size_t subnet_size1 = 23;
	size_t host_size = g_max_subnest_size - subnet_size1;
	size_t ip_var_left = (1 << host_size);
	dhcp_ty *dhcp = DHCPCreate(subnet_ip, subnet_size1);
	
	ip_var_left -= g_intialize_alloc_size;
	
	DHCPAllocateIp(dhcp, ip_address , requested_ip_address);
	DHCPAllocateIp(dhcp, ip_address1 , requested_ip_address1);
	DHCPAllocateIp(dhcp, ip_address2 , requested_ip_address2);
	puts("starting count and free test:");
	ip_var_left -= 3;
	assert (ip_var_left == DHCPCountFree(dhcp));
	puts("maximum ip_address");
	while (ip_var_left != 1)
	{
		assert(ALLOCATED_AVAILABLE_ADDRESS == 
		DHCPAllocateIp(dhcp, ip_address , requested_ip_address));
		--ip_var_left;
	}
	printf("%d.%d.%d.%d \n",
	        ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
	assert(1 == DHCPCountFree(dhcp));
	assert (FREE_SUCCESFULL ==  DHCPFreeIp(dhcp, ip_address));
	assert (FREE_SUCCESFULL ==  DHCPFreeIp(dhcp, ip_address1));
	/* trying to double free */
	assert(3 == DHCPCountFree(dhcp));
	assert (DOUBLE_FREE ==  DHCPFreeIp(dhcp, ip_address1));
	DHCPDestroy(dhcp);
	
}
static void SubnetZeroTest(void)
{
	unsigned char subnet_ip[] = {000, 000, 000, 000};
	unsigned char ip_address[4] = {0}; 
	size_t subnet_size1 = 8;	

	size_t host_size = g_max_subnest_size - subnet_size1;
	size_t ip_var_left = (1 << host_size);
	unsigned char requested_ip_address [] = { 000, 000, 000, 002};
	dhcp_ty *dhcp = DHCPCreate(subnet_ip, subnet_size1);
	ip_var_left -= g_intialize_alloc_size;
	assert(ALLOCATED_REQUSTED_ADDRESS == DHCPAllocateIp(dhcp, ip_address , requested_ip_address));
	DHCPDestroy(dhcp);
}