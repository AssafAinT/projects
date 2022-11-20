/*****************************************************
 * dlist WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Maayan Sheraizin                        *
 * date: 19.06.2022                                  *
 *****************************************************/
 
/********************************libraries includes****************************/
#include <stdio.h>	/* printf */
#include <assert.h> /*assert */

#include "dlist.h" /* slist */

/********************************Function Declaration**************************/

int SumFunc(void *first_num, void *sum);

int MatchFunc(const void *data, void *params); 

int DlistTest(void);
/********************************main******************************************/

int main(void)
{
	
	return (DlistTest());
}

/********************************Function Defenitions**************************/
int SumFunc(void *first_num, void *sum)
{
	*((int *)sum) += *((int *)first_num);
	
	return (0);
}

int MatchFunc(const void *data, void *params)
{
	
	return (data == params);
}

int DlistTest(void)
{
	int sum = 0;
	int gru = 121;
	int new_data = 16; 
	dlist_ty *new_dlist = DlistCreate();
	dlist_ty *dest = DlistCreate();
	dlist_iterator_ty first_iterator = NULL;
	dlist_iterator_ty second_iterator = NULL;
	
	assert(1 == DlistIsEmpty(new_dlist));
	assert(0 == DlistSize(new_dlist));
	
	first_iterator = DlistBegin(new_dlist);
	second_iterator = DlistBegin(new_dlist);
	printf("%p is first_iterator address\n", (void *)first_iterator);
	printf("%p is second_iterator address\n", (void *)second_iterator);
	assert(1 == DlistIterIsEqual(first_iterator, second_iterator));
	
	first_iterator = DlistInsertBefore(first_iterator, &gru);
	printf("%p is first_iterator address\n", (void *)first_iterator);
	first_iterator = DlistInsertBefore(first_iterator, &gru);
	printf("%p is first_iterator address\n", (void *)first_iterator);
	first_iterator = DlistInsertBefore(first_iterator, &gru);
	
	printf("%d in first iterator\n",*(int *)DlistGetData(first_iterator));
	printf("%p is first_iterator address\n", (void *)first_iterator);
	assert(3 == DlistSize(new_dlist));
	assert(0 == DlistForEach(first_iterator, second_iterator , SumFunc, &sum));
	printf("now sum is %d\n", sum);
	printf("%p is first_iterator address\n", (void *)first_iterator);
	DlistSetData(second_iterator, &new_data);
	printf("%p is second_iterator address\n", (void *)second_iterator);
	first_iterator = DlistBegin(new_dlist);
	printf("%p is first_iterator address\n", (void *)first_iterator);
	first_iterator = DlistFind(DlistBegin(new_dlist), second_iterator,	
					 MatchFunc, &new_data);
	assert(16 == *(int *)DlistGetData(first_iterator));
	assert(3 == DlistSize(new_dlist));
	assert(1== DlistMultiFind(DlistBegin(new_dlist), DlistEnd(new_dlist),dest, MatchFunc, &gru));
	
	assert(3 == DlistSize(dest));
	DlistSplice(DlistPrev(DlistEnd(new_dlist)), DlistBegin(dest), 
				DlistEnd(dest));
	
	assert(6 == DlistSize(new_dlist));
	assert(0 == DlistSize(dest));
	
	DlistDestroy(new_dlist);
	DlistDestroy(dest);
	
	return (0);
}
