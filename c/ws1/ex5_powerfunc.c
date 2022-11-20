#include <stdio.h>

double power(int n); /*function declartion */

int main()
{
	int n;
	
	printf("Enter a integer number:\n");
	scanf("%d", &n);
	printf("The result of 10 power %d is: %.5f\n", n, power(n));
	return 0;
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


