#include <stdio.h> /* for main */
#include <assert.h> /* assert */
#include <stdlib.h> /*for malloc */

void ValSwap( int *num1, int *num2 );
void ArrCpy(int *originl_arr, int *arr_copied, size_t array_size); 
void SizetSwap(size_t *var1, size_t *var2);
void ptrSizetSwap(size_t **ptr1, size_t **var2);
void PrintAdresses(void);

int main()
{
	int first_num = 0;
	int second_num = 0;
	
	size_t var1, var2;
	size_t *ptr1, *ptr2;
	size_t *ptr_address1, *ptr_address2;
	
	size_t arr_size = 6;
	char origin_arr[10] = "hello";
	char copy_array[6];
	var1 = 2;
	var2 = 3;
	ptr1 = &var1;
	ptr2 = &var2;
	
	ptr_address1 = (size_t *)&ptr1;
	ptr_address2 = (size_t *)&ptr2;
	
	
	ArrCpy(int *originl_arr, int *arr_copied, size_t array_size);
	
	printf("Enter two values that you want to swap saparated by a space\n");
	if (scanf("%d %d", &first_num, &second_num))
	{
		ValSwap( &first_num, &second_num);
		printf("Now the value of first num is %d and second val is %d\n",
		 first_num, second_num);
	}
	else
	{
		printf("Failed to read the numbers\n");

	}
	 
 	printf("var1 is now %lu and var2 is %lu\n", var1, var2);
	printf("ptr1 %lu address %p \nptr2 %luaddress %p\n", *ptr1, (void *)ptr1, *ptr2, (void *)ptr2);
	SizetSwap( ptr_address1, ptr_address2);
	printf("ptr1 %lu address %p \nptr2 %luaddress %p\n", *ptr1, (void *)ptr1, *ptr2, (void *)ptr2);
		printf("var1 is now %lu and var2 is %lu\n", var1, var2);
	SizetSwap(&var1, &var2);
	printf("var1 is now %lu and var2 is %lu\n", var1, var2);
	printf("ptr1 %lu address %p \nptr2 %luaddress %p\n", *ptr1, (void *)ptr1, *ptr2, (void *)ptr2);
	ptrSizetSwap( &ptr1, &ptr2);
	printf("ptr1 %lu address %p \nptr2 %luaddress %p\n", *ptr1, (void *)ptr1, *ptr2, (void *)ptr2);

	
	return (0);
}


void PrintAdresses(void)
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));
	
	if (ptr)
	{
		int **ptr3 = &ptr;
		printf("==%p==\n", (void *)&ptr3);
	}
	
	printf("==%p==\n", (void *)&s_i);
	printf("==%p==\n", (void *)&i);
	printf("==%p==\n", (void *)&ptr);
	printf("==%p==\n", (void *)&ptr2);
	
	
	free(ptr2);
	
}

void ValSwap( int *num1, int *num2 )
{
	assert( NULL != num1 );
	assert( NULL != num2 );
	
	if (num1 != num2 )
	{
		*num1 = *num1 + *num2;
		*num2 = *num1 - *num2;
		*num1 = *num1 - *num2;
	}
}
	
void ArrCpy(int *originl_arr, int *arr_copied, size_t array_size)
{
	size_t i = 0;
	assert ( NULL != original_arr);
	assert ( NULL != arr_copied);
	

	for(i=0; i < array_size; i++)
	{
		*(arr_copied+i) = *(originl_arr+i);
	}
}



void SizetSwap(size_t *var1, size_t *var2)
{
	size_t tmp;
	assert(var1 != NULL && var2 != NULL);
	tmp = *var1;
	*var1 = *var2;
	*var2 = tmp;
}

void ptrSizetSwap(size_t **ptr1, size_t **ptr2)
{
	size_t *tmp;
	assert(ptr1 != NULL && ptr2 != NULL);
	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}	
