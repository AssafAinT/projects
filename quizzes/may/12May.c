#include <stdio.h>   /* for testing */
#include <assert.h> /* for assert */
#include <ctype.h>  /* for tolower function */

void TF(int num); 
char *ReverseStr(char *str);

int main()
{
	int num_to_func = 0; 
	char to_rev[10] = "ASSSSSAf";
	
	ReverseStr(to_rev);
	printf("After reverse %s\n", to_rev);	
	printf("entered a number\n");
	
	if (scanf("%d", &num_to_func))
	{
		TF(num_to_func);
	}
	else
	{
		printf("You entered unvalid data\n");
	}
	return 0;
	
}

void TF(int num)
{
	while (num > 0)
	{
		if(num % 3 == 0 && num % 5 == 0)
		{
			printf("TF\n");
		}
		else if(num % 3 == 0)
		{
			printf("T\n");
		}
		else if(num % 5 == 0)
		{
			printf("F\n");
		}
		else
		{
			printf("%d\n", num);
		}
		--num;
	}
}


char *ReverseStr(char *str)
{

	char *head_str = str;
	char *tail_str = str;
	char temp = '\0';
	
	assert( NULL != str); 

	
	/* while loop for counting length and positioning tail string */
	while ('\0' != *tail_str)
	{
		
		++tail_str;
		
	}
	/* step backwark from null character */
	--tail_str; 
	
	while( head_str < tail_str )
	{
		temp = tolower(*tail_str);
		*tail_str = tolower(*head_str);
		*head_str = temp;
		
		--tail_str;
		++head_str;
	}
	return (str);
}
	
	
