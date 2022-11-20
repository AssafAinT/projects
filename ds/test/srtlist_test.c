/*****************************************************
 * Sorted list                                       *
 * Assaf Ainhoren                                    *
 * Reviewer: Avia Avikasis                           *
 * date: 19.06.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#define UNUSED(param)  (void)param

#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "srtlist.h" 

int CompareData(void *data1, void *data2 , void *params);
int SumFunc(void *first_num, void *sum);
int MatchFunc(const void *data, void *params); 

int main(void)
{	
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;
    int new_data = 0;
    int new_data2 = 9;
    
    srtlist_ty *list = SrtlistCreate(CompareData, NULL);
    srtlist_ty *list2 = SrtlistCreate(CompareData, NULL);
	srtlist_ty *list3 = SrtlistCreate(CompareData, NULL);
    
    srtlist_iterator_ty iterator;
    srtlist_iterator_ty iterator2;
    srtlist_iterator_ty iterator3;
    
    iterator = SrtlistInsert(list , &data2);
    assert(2 == *(int *)SrtlistGetData(iterator));
    
    iterator2 = SrtlistInsert(list2, &data5);
    assert(5 == *(int *)SrtlistGetData(iterator2));
    
    iterator3 =SrtlistInsert(list3 , &new_data);
    iterator3 =SrtlistInsert(list3 , &new_data2);
    
    iterator = SrtlistInsert(list , &data5);
    assert(5 == *(int *)SrtlistGetData(iterator));
    
    iterator = SrtlistInsert(list , &data3);
    assert(3 == *(int *)SrtlistGetData(iterator));
    iterator = SrtlistPrev(iterator);
    assert(2 == *(int *)SrtlistGetData(iterator));
    
    iterator = SrtlistInsert(list , &data1);
    assert(1 == *(int *)SrtlistGetData(iterator));
    iterator = SrtlistNext(iterator);
    assert(2 == *(int *)SrtlistGetData(iterator));
    
    iterator = SrtlistInsert(list , &data4);
    assert(4 == *(int *)SrtlistGetData(iterator));
    
    iterator = SrtlistBegin(list);
    assert(1 == *(int *)SrtlistGetData(iterator));
    
    iterator = SrtlistPrev(SrtlistEnd(list));
    assert(5 == *(int *)SrtlistGetData(iterator));
    
    assert(5 == (int)SrtlistSize(list));
    
    assert(0 == (int)SrtlistIterIsEqual(iterator, SrtlistBegin(list)));
    assert(1 == (int)SrtlistIterIsEqual(iterator, iterator));
    
    iterator = SrtlistFind(list, SrtlistBegin(list), SrtlistEnd(list), &data1);
    assert(1 == *(int *)SrtlistGetData(iterator));
    iterator = SrtlistBegin(list);
    iterator = SrtlistFindIf(SrtlistBegin(list), SrtlistEnd(list), MatchFunc, &data6);
	assert(1 == SrtlistIterIsEqual(iterator, SrtlistEnd(list)));
    SrtlistMerge(list, list3);
    assert(7 == SrtlistSize(list));
    assert(0 == (int)SrtlistIsEmpty(list2));
    assert(1 == (int)SrtlistIsEmpty(list3));
    
    assert(0 == (int)SrtlistIsEmpty(list));
    iterator = SrtlistBegin(list);
    iterator = SrtlistRemove(iterator);
    iterator = SrtlistRemove(iterator);
    iterator = SrtlistRemove(iterator);
    iterator = SrtlistRemove(iterator);
    iterator = SrtlistRemove(iterator);
    iterator = SrtlistRemove(iterator);
    /*
	#ifndef NDEBUG
		SrtlistFindIf(SrtlistBegin(list), SrtlistBegin(list2), MatchFunc, &data6);
	#endif*/
    assert(9 == *(int *)SrtlistGetData(iterator));
    iterator = SrtlistRemove(iterator);
    assert(1 == (int)SrtlistIsEmpty(list));
    
    SrtlistDestroy(list);
    SrtlistDestroy(list2);
    SrtlistDestroy(list3);
    
    return (0);
}

int CompareData(void *data1, void *data2 , void *params)
{
	UNUSED(params);
	
	return ((*(int *)(data1)) - (*(int *)data2));
}

int SumFunc(void *first_num, void *sum)
{
	*((int *)sum) += *((int *)first_num);
	
	return (0);
}

int MatchFunc(const void *data, void *params)
{
	
	return (data == params);
}
