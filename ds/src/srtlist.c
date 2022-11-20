/*****************************************************
 * Sorted list                                       *
 * Assaf Ainhoren                                    *
 * Reviewer: Avia Avikasis                           *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "srtlist.h"

struct srtlist 
{
    dlist_ty *dlist;
    compare_data_func sort;
    void *param;
};

static srtlist_iterator_ty FindToIter(srtlist_ty *dest_list,
                                  srtlist_iterator_ty to_iter,
                                  srtlist_iterator_ty where_iter,
                                  srtlist_ty *src_list); 

static srtlist_iterator_ty FindWhereToSplice(srtlist_ty *dest_list, 
                                     srtlist_iterator_ty where_runner,
                                     srtlist_iterator_ty from_iter);
/*----------------------------------------------------------------------------*/
/*                               SrtlistCreate                                */
/*----------------------------------------------------------------------------*/
srtlist_ty *SrtlistCreate(compare_data_func sort, void *param)
{
	srtlist_ty *new_srtlist = (srtlist_ty *)malloc(sizeof(srtlist_ty));
	if (NULL == new_srtlist)
	{
		return NULL;
	}
	new_srtlist->dlist = DlistCreate();
	if (NULL == new_srtlist->dlist)
	{
		free(new_srtlist);
		new_srtlist = NULL;
		return NULL;
	}
	new_srtlist->sort = sort;
	new_srtlist->param = param;
	return(new_srtlist);
}

/*----------------------------------------------------------------------------*/
/*                               SrtlistIsDestroy                             */
/*----------------------------------------------------------------------------*/
void SrtlistDestroy(srtlist_ty *srtlist)
{
	assert(NULL != srtlist);

	DlistDestroy(srtlist->dlist);
	
	free(srtlist);
	srtlist = NULL;
} 

/*----------------------------------------------------------------------------*/
/*                               SrtlistIsInsert                              */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistInsert(srtlist_ty *srtlist, void *data)
{
	srtlist_iterator_ty runner = {0};
	srtlist_iterator_ty iterator = {0};
	assert(NULL != srtlist);
	
	runner = SrtlistBegin(srtlist);
	
	
	while (!DlistIterIsEqual(runner.dlist_iterator, 
	       DlistEnd(srtlist->dlist)) &&
	       (0 <= srtlist->sort(data,
	       DlistGetData(runner.dlist_iterator),
	       srtlist->param)))
  	{
  		runner = SrtlistNext(runner);
  	}
  	
	iterator.dlist_iterator = DlistInsertBefore(runner.dlist_iterator, data);

     return (iterator);
}
/*----------------------------------------------------------------------------*/
/*                               SrtlistIsRemove                              */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistRemove(srtlist_iterator_ty iterator)
{
	assert(NULL != iterator.dlist_iterator);
	
	iterator.dlist_iterator = DlistRemove(iterator.dlist_iterator);
	
	return (iterator);

}
/*----------------------------------------------------------------------------*/
/*                               SrtlistIsBegin                               */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistBegin(const srtlist_ty *srtlist)
{
	srtlist_iterator_ty begin_iterator = {0};
	assert(NULL != srtlist);
	
	begin_iterator.dlist_iterator = DlistBegin(srtlist->dlist); 
	
	#ifndef NDEBUG
	begin_iterator.srtlist = srtlist->dlist;
	#endif


	return (begin_iterator);
}
/*----------------------------------------------------------------------------*/
/*                               SrtlistIsNext                                */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistEnd(const srtlist_ty *srtlist)
{
	srtlist_iterator_ty end_iterator = {0};
	assert(NULL != srtlist);
	
	end_iterator.dlist_iterator = DlistEnd(srtlist->dlist);
	
	#ifndef NDEBUG
	end_iterator.srtlist = srtlist->dlist;
	#endif


	return (end_iterator);
}
/*----------------------------------------------------------------------------*/
/*                               SrtlistIsNext                                */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistNext(srtlist_iterator_ty iterator)
{
	srtlist_iterator_ty next_iterator = {0};
	assert(NULL != iterator.dlist_iterator);
	
	next_iterator.dlist_iterator = DlistNext(iterator.dlist_iterator);
	
	return (next_iterator);
}
/*----------------------------------------------------------------------------*/
/*                               SrtlistPrev                                  */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistPrev(srtlist_iterator_ty iterator)
{
	srtlist_iterator_ty prev_iterator = {0};
	assert(NULL != iterator.dlist_iterator);
	
	prev_iterator.dlist_iterator = DlistPrev(iterator.dlist_iterator);
	
	return (prev_iterator);
}
/*----------------------------------------------------------------------------*/
/*                               SrtlistGetData                               */
/*----------------------------------------------------------------------------*/
void *SrtlistGetData(srtlist_iterator_ty iterator)
{
	assert(NULL != iterator.dlist_iterator);
	
	return (DlistGetData(iterator.dlist_iterator));
}
/*----------------------------------------------------------------------------*/
/*                               SrtlistSize                                  */
/*----------------------------------------------------------------------------*/
size_t SrtlistSize(const srtlist_ty *srtlist)
{
	assert(NULL != srtlist);
	
	return (DlistSize(srtlist->dlist));
}

/*----------------------------------------------------------------------------*/
/*                               SrtlistIsEmpty                               */
/*----------------------------------------------------------------------------*/
int SrtlistIsEmpty(const srtlist_ty *srtlist)
{
	assert(NULL != srtlist);
	
	return (DlistIsEmpty(srtlist->dlist));
}
/*----------------------------------------------------------------------------*/
/*                               SrtListIterIsEqual                           */
/*----------------------------------------------------------------------------*/
int SrtlistIterIsEqual(srtlist_iterator_ty iterator1,
					   srtlist_iterator_ty iterator2)
{
	assert(NULL != iterator1.dlist_iterator);
	assert(NULL != iterator2.dlist_iterator);
	
	return (DlistIterIsEqual(iterator1.dlist_iterator,
	        iterator2.dlist_iterator));
	
}

/*----------------------------------------------------------------------------*/
/*                               SrtListForEach                               */
/*----------------------------------------------------------------------------*/
int SrtlistForEach(srtlist_iterator_ty from, srtlist_iterator_ty to, 
                  action_ty action_func, void *param)
{
	assert(NULL != from.dlist_iterator);
	assert(NULL != to.dlist_iterator);
	assert(NULL != action_func);
	
	#ifndef NDEBUG
		assert(from.srtlist == to.srtlist);
	#endif
	return (DlistForEach(from.dlist_iterator,
	       to.dlist_iterator, 
	       action_func, param));
}

/*----------------------------------------------------------------------------*/
/*                               SrtListFindIf                                */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistFindIf(srtlist_iterator_ty from,
                                  srtlist_iterator_ty to, 
                                  is_match_ty match_func,
                                   void *param)
{
	srtlist_iterator_ty ret = {0};
	#ifndef NDEBUG
		assert(from.srtlist == to.srtlist);
	#endif
	ret.dlist_iterator = DlistFind(from.dlist_iterator,
	       to.dlist_iterator,
	       match_func, 
	       param);
	       
	return (ret);
}

/*----------------------------------------------------------------------------*/
/*                               SrtListFind                                  */
/*----------------------------------------------------------------------------*/
srtlist_iterator_ty SrtlistFind(const srtlist_ty *srtlist,
                                srtlist_iterator_ty from,
                                srtlist_iterator_ty to, 
                                void *data_to_find)
{
	int func_res = 0;
	#ifndef NDEBUG
		assert(from.srtlist == to.srtlist);
		assert (NULL != from.dlist_iterator);
		assert (NULL != to.dlist_iterator);
	#endif
	
	for ( ; !SrtlistIterIsEqual(from, to);
	         from = SrtlistNext(from))
	{
		func_res = srtlist->sort(SrtlistGetData(from), 
				  data_to_find,
		          srtlist->param);
		
		if ( 0 == func_res)
		{
			return (from);
		}	
	}
	return (to);
}

/*----------------------------------------------------------------------------*/
/*                               Merge                                        */
/*----------------------------------------------------------------------------*/
void SrtlistMerge(srtlist_ty *dest_list , srtlist_ty *src_list)
{
    srtlist_iterator_ty from_iter = {0};
    srtlist_iterator_ty to_iter = {0};
    srtlist_iterator_ty where_iter = {0};
        
    assert(NULL != dest_list);
    assert(NULL != src_list);
    
    where_iter = SrtlistBegin(dest_list);
    from_iter = SrtlistBegin(src_list);
    to_iter = SrtlistBegin(src_list);
    
    while (!SrtlistIterIsEqual(from_iter, SrtlistEnd(src_list)))
    {
        where_iter = FindWhereToSplice(dest_list, where_iter, from_iter);
                                        
        to_iter = FindToIter(dest_list, to_iter, where_iter, src_list);
        
        DlistSplice(where_iter.dlist_iterator,
                    from_iter.dlist_iterator,
                    to_iter.dlist_iterator);
        
        from_iter = to_iter;
    }
}

static srtlist_iterator_ty FindWhereToSplice(srtlist_ty *dest_list, 
                                     srtlist_iterator_ty where_runner,
                                     srtlist_iterator_ty from_iter)
{
	while ((!SrtlistIterIsEqual(where_runner, SrtlistEnd(dest_list)) &&
            (0 >= dest_list->sort(
                            SrtlistGetData(where_runner),
                             SrtlistGetData(from_iter), dest_list->param))))
    
    {
        where_runner = SrtlistNext(where_runner);
    } 
    return (where_runner);

}

static srtlist_iterator_ty FindToIter(srtlist_ty *dest_list,
                                  srtlist_iterator_ty to_iter,
                                  srtlist_iterator_ty where_iter,
                                  srtlist_ty *src_list)
{

	to_iter = SrtlistNext(to_iter);
	
	while ((NULL != DlistNext(to_iter.dlist_iterator)&&
	       ((!SrtlistIterIsEqual(to_iter,
           SrtlistEnd(src_list)) &&
           0 >= dest_list->sort(SrtlistGetData(to_iter),
                                SrtlistGetData(where_iter),
                                dest_list->param)))))
           {
           		to_iter = SrtlistNext(to_iter);
           }

    return (to_iter);
}
