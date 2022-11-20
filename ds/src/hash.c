/*****************************************************
 * HASH_TABLE                                        *
 * Assaf Ainhoren                                    *
 * Reviewer: Ahron Cohen                             *
 * date: 17.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "hash.h"
#include "dlist.h"

#define SUCCESS 0
#define FAIL 1 
#define HASH_EMPTY 0
struct hash_table 
{
    dlist_ty **lists_array;
    size_t size;
    hash_function hash_func;
    is_match_func is_match_func;
};

static size_t GetListArraySize(const hash_table_ty *hash);
static dlist_ty *FindListToInsertHash(hash_table_ty *hash_table,
                                     void *data);
static void *HashGetData(hash_table_ty *hash_table, dlist_ty *desired_list,
                                                                void *data);
hash_table_ty *HashTableCreate(hash_function  hash_func,
                               is_match_func is_match,
                               size_t hash_size)
{
	hash_table_ty *hash_to_ret = NULL;
	size_t desired_size = 0;
	assert(NULL != hash_func);
	assert(NULL != is_match);
	
	hash_to_ret = (hash_table_ty *)malloc(sizeof(hash_table_ty));
	if (NULL == hash_to_ret)
	{
		return (NULL);
	}
	
	hash_to_ret->size = hash_size;
	hash_to_ret->hash_func = hash_func;
	hash_to_ret->is_match_func = is_match;
	
	hash_to_ret->lists_array = (dlist_ty **)malloc(hash_size *sizeof(dlist_ty *));
	if (NULL == hash_to_ret->lists_array)
	{
		free(hash_to_ret);
		hash_to_ret = NULL;
		return (NULL);
	}
	
	for ( ; desired_size < hash_size; ++desired_size)
	{
		hash_to_ret->lists_array[desired_size] = DlistCreate();
		if (NULL == hash_to_ret->lists_array[desired_size])
		{
			HashTableDestroy(hash_to_ret);
			return (NULL);
		}
	}
	
	return (hash_to_ret);
	
}

void HashTableDestroy(hash_table_ty *hash_table)
{
	size_t i = 0;
	
	assert(NULL != hash_table);
	for ( ; i < GetListArraySize(hash_table); ++i)
	{
		DlistDestroy(hash_table->lists_array[i]);
		hash_table->lists_array[i] = NULL;
	}
	free(hash_table->lists_array);
	hash_table->lists_array = NULL;
	free(hash_table);
	hash_table = NULL;
	
}

int HashTableInsert(hash_table_ty *hash_table, void *data)
{
	dlist_ty *desired_dlist = NULL;
	assert(NULL != hash_table);
	
	
	desired_dlist = FindListToInsertHash(hash_table, data);
	if(NULL == desired_dlist)
	{
		return (FAIL);
	}

	return(DlistIterIsEqual(DlistEnd(desired_dlist),
	           DlistInsertBefore(DlistBegin(desired_dlist), (void *)data)));
}

int HashTableRemove(hash_table_ty *hash_table, void *data)
{
	dlist_ty *desired_dlist = NULL;
	dlist_iterator_ty found= NULL;

	assert(NULL != hash_table);
	
	
	desired_dlist = FindListToInsertHash(hash_table, data);
	if(NULL == desired_dlist)
	{
		return (FAIL);
	}	
	found = DlistRemove(DlistFind(DlistBegin(desired_dlist), DlistEnd(desired_dlist),
	                  hash_table->is_match_func, data));
	
	if (DlistIterIsEqual(DlistEnd(desired_dlist), found))
	{
		return (FAIL);
	}
	
	return(SUCCESS);
}

void *HashTableFind(hash_table_ty *hash_table, void *data)
{
	dlist_ty *desired_dlist = NULL;
	dlist_iterator_ty found = NULL;
	assert(NULL != hash_table);
	
	
	desired_dlist = FindListToInsertHash(hash_table, data);
	if(NULL == desired_dlist)
	{
		return (NULL);
	}
	found = DlistFind(DlistBegin(desired_dlist), DlistEnd(desired_dlist),
	                  hash_table->is_match_func, data);
	
	if (DlistIterIsEqual(DlistEnd(desired_dlist), found))
	{
		return (NULL);
	}
		
	return(HashGetData(hash_table, desired_dlist, data));
}

size_t HashTableSize(const hash_table_ty *hash_table)
{
	size_t counter = 0;
	size_t i = 0;
	assert(NULL != hash_table);
	
	for ( ; i < GetListArraySize(hash_table); ++i)
	{
		counter += DlistSize(hash_table->lists_array[i]);
	}
	return(counter);
}

int HashTableIsEmpty(const hash_table_ty *hash_table)
{
	assert(NULL != hash_table);
	
	return (HASH_EMPTY == HashTableSize(hash_table));
}

int HashTableForEach(hash_table_ty *hash_table,
                      action_func action_func, void *param)
{
	size_t i = 0;
	dlist_ty *dlist = NULL;
	int ret_stat = SUCCESS;
	assert(NULL != hash_table);
	for ( ; i < GetListArraySize(hash_table) && SUCCESS == ret_stat ; ++i)
	{
		dlist = hash_table->lists_array[i];
		ret_stat = DlistForEach(DlistBegin(dlist),
		           DlistEnd(dlist), action_func, param);
		
	}
	return (ret_stat);
}

/* advanced */

double HasTableLoad(const hash_table_ty  *hash_table);

double HashTableSD(const hash_table_ty *hash_table);

/*************************************static function**************************/

static size_t GetListArraySize(const hash_table_ty *hash)
{
	assert(NULL != hash);
	
	return(hash->size);
}

static dlist_ty *FindListToInsertHash(hash_table_ty *hash_table,
                                     void *data)
{
	size_t insert_index = 0;
	assert(NULL != hash_table);
	
	insert_index = hash_table->hash_func(data);
	if (insert_index > GetListArraySize(hash_table))
	{
		return (NULL);
	}
	return(hash_table->lists_array[insert_index]);
}

static void *HashGetData(hash_table_ty *hash_table, dlist_ty *desired_list,
                                                                void *data)
{
	assert(NULL != hash_table);
	assert(NULL != desired_list);
	
	return (DlistGetData(DlistFind(DlistBegin(desired_list),
	                              DlistEnd(desired_list),
	                              hash_table->is_match_func, data)));
}
