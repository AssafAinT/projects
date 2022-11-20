#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
	char str1[] = "hello";
	char str2[6];
	char *str3_head = NULL;
	char *str1_head = str1; 
	
	char *str3 = (char *)malloc((strlen(str1)+1));
	if (NULL == str3)
	{
		return (1);
	}
	
	str3_head = str3;
		
	while (*str1_head)
	{
		*str3 = *str1_head;
		++str3;
		++str1_head;
	}
	

	strcpy(str2, str1);
	
	if(islower(*str1))
	{
		*str1 = toupper(*str1);
	}
	
	printf("This is str1: %s\n", str1);
	
	free(str3_head);
	str3 = NULL;
	
	return (0);
}

/*********************************************************************************/
/*********************Question 2 - Bridge Crossing *******************************
* A= 1 B = 2 C = 4 D = 5                                                         *
* First go A+B than B returns we are on 4 minutes,than C+D CROSS,Than A returns  *
* We Are on 10 minutes, than a+b cross = 12 minutes                              *
*********************************************************************************/

/*********************************************************************************/
/*********************Question 3 - Rope Burnout    *******************************
*  2 edges of 1 rope ignite together second rope only 1 edge                     *
*  when the second rope get to the middle i ignite the 3rd rope		      *
*  when the 2nd rope totaly burn i ignite the leftout edge of 3rd rope           *
*  when both edges of rope 3 meet together we are on 1:15 hour.                  *
**********************************************************************************/

