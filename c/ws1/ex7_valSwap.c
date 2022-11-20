#include <stdio.h>
#include <assert.h>

void valSwap( int *num1, int *num2 );

int main()
{
	int first_num, second_num;
	printf("Enter two values that you want to swap saparated by a space\n");
	scanf("%d %d", &first_num, &second_num);
	valSwap( &first_num, &second_num);
	printf("Now the value of first num is %d and second val is %d\n",
	 first_num, second_num);
	return 0;
}


void valSwap( int *num1, int *num2 )
{
	assert( num1 != NULL && num2 != NULL);
	
	if (num1 != num2 )
	{
		*num1 = *num1 + *num2;
		*num2 = *num1 - *num2;
		*num1 = *num1 - *num2;
	}
}
	
