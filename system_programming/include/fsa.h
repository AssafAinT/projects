#ifndef __ILRD_OL127_128_FSA_H__
#define __ILRD_OL127_128_FSA_H__
/*****************************************************
* FSA                                               *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 27.06.2022                                  *
*****************************************************/



/********************************libraries includes****************************/
#include <stddef.h> /*size_t */
typedef struct fsa fsa_ty;

/*****************************************************
* Description: Initializing FSA                      *
* PARARMS:                                           *
* 		 memory - a pointer to beginning of the pool *
* 		 pool_size - pool size in bytes              *
* 		 block_size - block size in bytes            *
* Return value: The Pointer to the FSA               *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
fsa_ty *FsaInit(void *memory, size_t pool_size, size_t block_size);
/*****************************************************
* Description: Allocate memory in The FSA            *
* PARARMS:                                           *
* 		 fsa - a pointer to the fsa to alloc from    *
* Return value: The Pointer allocated memory         *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void *FsaAlloc(fsa_ty *fsa);
/*****************************************************
* Description: free a block in The FSA               *
* PARARMS:                                           *
* 		 fsa - a pointer to the fsa                  *
* 		 ptr - the address to free                   *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void FsaFree(fsa_ty *fsa, void *ptr);
/*****************************************************
* Description: Count how many blocks can be used     *
* PARARMS:                                           *
* 		 fsa - a pointer to the fsa                  *
* Return value: The the number of free blocks        *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
size_t FsaCountFreeBlock(const fsa_ty *fsa);
/*****************************************************
* Description: Suggest the pool_size for the FSA     *
* PARARMS:                                           *
* 		 num_blocks -desired num of blocks           *
* 		 block_size - fixed size block in bytes      *
* Return value: size of pool in bytes                *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
size_t FsaSuggestSize(size_t num_blocks, size_t block_size);



#endif /* #ifndef __ILRD_OL127_128_FSA_H__ */ 
