#include <stdio.h>   /* for main    */
#include <stdlib.h>  /* for malloc */
#include <assert.h> /* for assert */

void valSwap( int *num1, int *num2 );
double power(int n);

int main()
{
	int num;			                                         /* for reversed number */
	int rem;
	int flag = 1;
	int reverse = 0; 
	
	int first_num, second_num;                                                /* for val swap */
	
	int pow_num = 0;
	
	printf("Enter a integer number:\n");
	scanf("%d", &pow_num);
	printf("The result of 10 power %d is: %.5f\n", pow_num, power(pow_num));
	
	printf("Enter a number you would like to reverse:\n");
	scanf("%d", &num);
	
	if (num < 0 )
	{
		flag = - 1;
	}
	
	while ( 0 != num )
	{
	rem = num % 10;
	reverse = ( reverse * 10 ) + rem;
	num /=10;
	}
	
	printf("The reversed number is %d\n", ( flag * reverse ));
	
	printf("\"\x48\x65\x6C\x6C\x6F\x20\x57\x6F\x72\x6C\x64\x21\"\n"); /*print if hx */
	
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



double power(int n)
{
	double result = 1; 
	double x = 10;
	int i;
	
	
	if ( n<0 )
	{
	n = (-1) * n;
	x = 1 / x;
	}
	
	for ( i=0; i<n; i++)
	{
		result = result * x ;
	}
	return result;
}
	
