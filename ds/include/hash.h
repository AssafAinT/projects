#ifndef __ILRD_OL_127_128_HASH_TABLE_H__
#define __ILRD_OL_127_128_HASH_TABLE_H__
/*****************************************************
 * HASH_TABLE                                        *
 * Assaf Ainhoren                                    *
 * Reviewer: Gal Cohen                               *
 * date: 19.06.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/

typedef struct hash_table hash_table_ty;
/* typedef for user's hash_function */
typedef size_t (*hash_function)(const void *data);
/* typedef for user's match function to retrieve data from hash_table */
typedef int (*is_match_func)(const void *hash_data, void *user_data);
/* typedef for user's action function to manipulate data in hash_table */
typedef int(*action_func)(void *data, void *param);


/*****************************************************
* Description: Creating the HASH_TABLE               *
* PARARMS:                                           *
* 		 hash_func - hash function for hashing       *
*        is_match - for matching                     *
		size - the size of addresess                 *
* Return value: The Pointer to the HASH_TABLE        *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(n).                                       *
*****************************************************/
hash_table_ty *HashTableCreate(hash_function  hash_func,
                               is_match_func is_match,
                               size_t hash_size);
/*****************************************************
* Description: Destroying the HASH_TABLE             *
* PARARMS:                                           *
		hash_table - hash_table to destroy           *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
void HashTableDestroy(hash_table_ty *hash_table);
/*****************************************************
* Description: Inserting data to the HASH_TABLE      *
* PARARMS:                                           *
		hash_table - hash_table to insert data to    *
		data - the data to insert                    *
* Return value: Upon Success 1                       *
*			upon failure : 0                         *
* Complexity:                                        *
* Time - O(1)                                        *
* Space -O(1).                                       *
*****************************************************/
int HashTableInsert(hash_table_ty *hash_table, void *data);
/*****************************************************
* Description: remove data from the HASH_TABLE       *
* PARARMS:                                           *
		hash_table - hash_table to remove from       *
		data - the data to remove                    *
* Return value: Upon Success 1                       *
*			upon failure : 0                         *
* Complexity:                                        *
* Time - O(1) amortised worst case O(n)              *
* Space -O(1).                                       *
*****************************************************/
int HashTableRemove(hash_table_ty *hash_table, void *data);
/*****************************************************
* Description: find data in the  HASH_TABLE          *
* PARARMS:                                           *
		hash_table - hash_table to find data  from   *
		data - the data to find                      *
* Return value: the data                             *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(1) amortised worst case O(n)              *
* Space -O(1).                                       *
*****************************************************/
void *HashTableFind(hash_table_ty *hash_table, void *data);
/*****************************************************
* Description: find the size of occupied space       *
*              in the  HASH_TABLE                    *
* PARARMS:                                           *
		hash_table - hash_table to size              *
* Return value: the size of occupied space in bytes  *
* Complexity:                                        *
* Time - O(n)                                        *
* Space -O(1).                                       *
*****************************************************/
size_t HashTableSize(const hash_table_ty *hash_table);
/*****************************************************
* Description: computes the emptiness  of HASH_TABLE *
*              in the  HASH_TABLE                    *
* PARARMS:                                           *
		hash_table - the hash table to check         *
* Return value: the size of occupied space in bytes  *
* Complexity:                                        *
* Time - O(n)                                        *
* Space -O(1).                                       *
*****************************************************/
int HashTableIsEmpty(const hash_table_ty *hash_table);
/*****************************************************
* Description:executing a user function over the data*
* PARARMS:                                           *
		hash_table - the hash table to check         *
* Return value: the size of occupied space in bytes  *
* Complexity:                                        *
* Time - O(n)                                        *
* Space -O(1).                                       *
*****************************************************/
int HashTableForEach(hash_table_ty *hash_table,
                      action_func action_func, void *param);

/* advanced */

double HasTableLoad(const hash_table_ty  *hash_table);

double HashTableSD(const hash_table_ty *hash_table);

#endif /* __ILRD_OL_127_128_HASH_TABLE_H__ */
