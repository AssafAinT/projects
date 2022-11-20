#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SPACE_CHARACTER 32

void ReverseWord(char *string);
void ReverseStr(char *start, char *end);
int main()
{
	char original_word[20] = "i am student";
	ReverseWord(original_word);
	printf("%s\n", original_word);
	
	return (0);
}

void ReverseWord(char *string)
{
	char *head = string;
	char *temp_str = string;

	assert(NULL != string);

	while('\0' != *temp_str)
	{	
		++temp_str;
		if('\0' == *temp_str)
		{
			ReverseStr(head, temp_str-1);
		}
		else if(*temp_str == SPACE_CHARACTER)
		{
			ReverseStr(head, temp_str-1);
			head = temp_str +1;
		}
	}
	ReverseStr(string, temp_str-1);
	
}

void ReverseStr(char *start, char *end)
{
	char ch;
	
	while(start < end)
	{
		ch = *start;
		*start = *end;
		*end = ch;
		++start;
		--end;
	}
	
}

