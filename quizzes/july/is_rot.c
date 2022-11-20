#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
int main(void)
{
	char *str1 = "12345";
	char *str2 = "23451";
	char *str3 = "6543";
	assert(1 == IsRotation(str1, str2));
	assert(0 == IsRotation(str1, str3));
	return (0);
}

int IsRotation(char *s1, char *s2)
{
	char *s3 = NULL;
	int is_rot = 0;
	
	size_t size_str = strlen(s1);
	
	if (strlen(s1) != strlen(s2))
	{
		is_rot = 0;
	}
	else
	{
		s3 = calloc((2 * (size_str+1)), sizeof(char));
		strcat(s3, s1);
		strcat(s3, s1);
		if (NULL != strstr(s3,s2))
		{
			is_rot = 1;
			
		}
	free(s3);
	}
	return (is_rot);
}

