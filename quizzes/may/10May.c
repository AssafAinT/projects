#include <stdio.h>

int main()
{
	int num = 1;
	const int num2 = 6;
	const int num3 = num2 - 5;
	char ch = '0';
	
	
	printf("%d\n", num);
	if (scanf("%d", &num))
	{
	
		printf("100 divided by %d is %f\n", num, 100/(float)num);
		printf("%d\n", num3);
		num =(int)4.7 * (int)ch;
		*((float *)&num) = 4.7;
		num *= 2;
		++num;
	}
	else
	{
		printf("Failed to read the numbers\n");
	}
	return (0);
}

