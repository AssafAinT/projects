#include <stdio.h>
#include <string.h>
#include <stddef.h>

int RoatateAndCheck(char *s1, char *s2, size_t size);
int IsARotation(char *s1, char *s2);
int main()
{
	char string1[6] = "12345";
	char string2[6] = "54123";
	
	printf("%d returned from the function\n", IsARotation(string1, string2));
	


	return (0);
}

int IsARotation(char *s1, char *s2)
{
	char *s1_start = s1;
	char *s2_start = s2;
	size_t size = strlen(s1);
	size_t i = 0;
	
	if (strlen(s1) != strlen(s2))
	{
		return (-1);
	}
	
	for(i = 0; i < size; ++i)
	{
		if(0 == RoatateAndCheck(s1_start, s2_start, size))
		{
			return 0;
		}
	}
	
	return 1;
}

int RoatateAndCheck(char *s1, char *s2, size_t size)
{
	char temp = '\0';
	size_t i = 0;
	--size;
	i = size;
	
	temp = s1[size];
	for(i = size; i > 0; --i)
	{
		s1[i] = s1[i -1];
	}
	s1[0] = temp;
	
	return strcmp(s1, s2);
}
