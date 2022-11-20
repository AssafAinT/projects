#include <stdio.h>

int main()
{
	
	int num;
	int rem;
	int flag = 1;
	int reverse = 0; 
	
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
}

