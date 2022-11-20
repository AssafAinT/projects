/********************************************************
 * dhcp                                                 *
 * Assaf Ainhoren                                       *
 * Reviewer: Ester Shpoker                              *
 * date: 4.08.2022                                      *
 * Description: The Dynamic Host Configuration Protocol *
 * (DHCP) is a network management protocol              *
 * used on Internet Protocol (IP) networks for          *
 * automatically assigning IP addresses                 *
 * and other communication parameters                   *
 * to devices connected to the network                  *
 * using a client–server architecture.                  *
 ********************************************************/
#ifndef __ILRD_127_128_DHCP_H__
#define __ILRD_127_128_DHCP_H__

#include <stddef.h> /* size_t */

typedef enum
{
    ALLOCATED_REQUSTED_ADDRESS = 0,
    ALLOCATED_AVAILABLE_ADDRESS = 1,
    FAILED_TO_ALLOCATE = 2,
    DOUBLE_FREE = 3,
    FREE_SUCCESFULL = 4
} return_status_ty;

typedef struct dhcp dhcp_ty;

/*****************************************************
* Description: Create DHCP                           *
* Params: *subnet_ip - subnet part of the IP address *
*          subnet_size - size of the subnet in bits  *
* return value: a ptr to the new DHCP                *
            Upon failure: NULL                       *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1)                                      *
******************************************************/
dhcp_ty *DHCPCreate(const unsigned char *subnet_ip, size_t subnet_size);
/*****************************************************
 * Description: Destroy DHCP                          *
 * Params: dhcp - the dhcp to destroy                 *
 * return value: void                                 *
 * Complexity:                                        *
 * Time - O(n).                                       *
 * Space - O(1)                                       *
 ******************************************************/
void DHCPDestroy(dhcp_ty *dhcp);
/*****************************************************
 * Description: allocate ip                           *
 * Params: dhcp - the dhcp to allocate from           *
 *         o_ip_address - user-buffer for ip address  *
 *         requested_ip_address - required ip address *
 * return value: Upon succes:                         *
 *                    ALLOCATED_REQUSTED_ADDRESS      *
 *                    ALLOCATED_AVAILABLE_ADDRESS     *
 *                Upon failure:                       *
 *                    FAILED_TO_ALLOCATE              *
 *                failed to allocate could be         *
 *                a result of exceeding limit of ip's *
 *                or memory insuffient                *
 * Complexity:                                        *
 * Time - O(logn).                                    *
 * Space - O(logn)                                    *
 ******************************************************/
return_status_ty DHCPAllocateIp(dhcp_ty *dhcp, unsigned char *o_ip_address,
                                const unsigned char *requested_ip_address);
/*****************************************************
 * Description: free ip                               *
 * Params: dhcp - the dhcp to free ip from            *
 *         ip_to_free - required ip address to free   *
 * return value: Success if successful                *
 *                Upon failure:                       *
 *                    DOUBLE_FREE                     *
 * Complexity:                                        *
 * Time - O(logn)                                     *
 * Space - O(1)                                       *
 ******************************************************/
return_status_ty DHCPFreeIp(dhcp_ty *dhcp, const unsigned char *ip_to_free);
/*****************************************************
 * Description: count free ip addresses left          *
 * Params: dhcp - the dhcp to free ip from            *
 * return value: free ip addresses left               *
 * Complexity:                                        *
 * Time - O(n)                                        *
 * Space - O(1)                                       *
 ******************************************************/
size_t DHCPCountFree(const dhcp_ty *dhcp);

#endif /* __ILRD_127_128_DHCP_H__ */