/*****************************************************
 * Slisr WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Haggai Newman                           *
 * date: 05.06.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "slist.h" /* slist */
/********************************Function Declaration**************************/

int SumFunc(void *first_num, void *sum);

int MatchFunc(const void *data, const void *params);

/********************************main******************************************/
int main()
{
	slist_ty *new_list = SlistCreate();
	slist_ty *second_list = SlistCreate();
	
	slist_iterator_ty iterator_first = NULL;
	slist_iterator_ty iterator_second = NULL;	
	slist_iterator_ty iterator_of_new = NULL;
	
	int sum = 0;
	int x = 100;
	int y = 101;
	
	int new_list_data = 26;
	
	iterator_first = SlistBegin(new_list);
	
	
	SlistInsertBefore(iterator_first, &x);
	
	iterator_of_new = SlistBegin(second_list);
	SlistInsertBefore(iterator_of_new, &new_list_data);
	
	iterator_first = SlistNext(iterator_first);
	
	SlistInsertBefore(iterator_first, &x);
	
	SlistSetData(iterator_first, &y);
	
	SlistInsertBefore(iterator_first, &x);
	
	iterator_first = SlistNext(iterator_first);
	
	iterator_second = SlistBegin(new_list);
	
	iterator_first = SlistEnd(new_list);
	
	printf("%d from isequal\n",SlistIterIsEqual(iterator_first,
	 						  iterator_second));
	 						  
  	/* trying to read from dummy */
	printf("%c from first iterator, %c from second iterator\n", *(char *)SlistGetData(iterator_first), *(char*)SlistGetData(iterator_second));
	
	SlistInsertBefore(iterator_first, &x);
	
	iterator_first = SlistBegin(new_list);
	
	SlistRemove(iterator_first); 
	
	iterator_second = SlistNext(iterator_second);
	
	printf("%d from isequal\n",SlistIterIsEqual(iterator_first,
	 						  iterator_second));
	 						  
	printf("%c from first iterator, %c from second iterator\n", 
							*(char *)SlistGetData(iterator_first), 
							*(char*)SlistGetData(iterator_second));
	
	printf("list size: %ld\n", SlistSize(new_list));
	
	iterator_first = SlistBegin(new_list);
	iterator_second = SlistEnd(new_list); 
	

	assert(0 == SlistForEach(iterator_first, iterator_second , SumFunc, &sum));

	printf("now sum is %d\n", sum);
	SlistAppend(new_list, second_list);
	
	iterator_first = SlistFind(iterator_first, iterator_second, 
	MatchFunc, &new_list_data);
	
	printf("%d from first iterator\n", *(int *)SlistGetData(iterator_first));

	SlistDestroy(new_list);
	

	return (0);
}

/********************************Function Defenitions**************************/
int SumFunc(void *first_num, void *sum)
{
	*((int *)sum) += *((int *)first_num);
	
	return (0);
}

int MatchFunc(const void *data, const void *params)
{
	
	return (data == params);
}

