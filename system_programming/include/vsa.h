#ifndef __ILRD_OL127_128_VSA_H__
#define __ILRD_OL127_128_VSA_H__
/*****************************************************
* VSA                                               *
* Assaf Ainhoren                                    *
* Reviewer: Mark Galperin                           *
* date: 27.06.2022                                  *
*****************************************************/



/********************************libraries includes****************************/
#include <stddef.h> /*size_t */
typedef struct vsa vsa_ty;

/*****************************************************
* Description: Initializing VSA                      *
* PARARMS:                                           *
* 		 memory - a pointer to beginning of the pool *
* 		 pool_size - pool size in bytes              *
* Return value: The Pointer to the VSA               *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
vsa_ty *VsaInit(void *memory, size_t pool_size);
/*****************************************************
* Description: Allocate memory in The VSA            *
* PARARMS:                                           *
* 		 pool - a pointer to the vsa to alloc from   *
* 		 block_size - size of block to alloc         *
* Return value: The Pointer allocated memory         *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
void *VsaAlloc(vsa_ty *pool, size_t block_size);
/*****************************************************
* Description: free a block in The VSA               *
* PARARMS:                                           *
* 		 ptr - the address to free                   *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void VsaFree(void *ptr);
/*****************************************************
* Description: Checking for the biggest chunk        *
     of memory available                             *
* PARARMS:                                           *
* 		 pool - a pointer to the vsa                 *
* Return value:The biggest block available for alloc *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
size_t VsaBiggestChunkAvailable(vsa_ty *pool);

#endif /* __ILRD_OL127_128_VSA_H__ */ 
