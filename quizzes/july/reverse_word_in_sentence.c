#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#define SPACE_ASCII 32
void ReverseWordInSentence(char *string);
static void ReverseStr(char *head, char *tail);



int main()
{
	char to_reverse_word[20] = "i am student";
	char to_reverse_word1[] = "binary search is fantastic";
	ReverseWordInSentence(to_reverse_word);
	printf("%s\n", to_reverse_word);
	ReverseWordInSentence(to_reverse_word1);
	printf("%s\n", to_reverse_word1);
	return (0);
}


void ReverseWordInSentence(char *string)
{
	char *head_str = string;
	char *tail_str = string;
	
	assert(NULL != string);
	
	while('\0' != *tail_str)
	{	
		++tail_str;
		if('\0' == *tail_str)
		{
			ReverseStr(head_str, tail_str-1);
		}
		else if(*tail_str == SPACE_ASCII)
		{
			ReverseStr(head_str, tail_str-1);
			head_str = tail_str +1;
		}
	}
	ReverseStr(string, tail_str-1);
	
}

static void ReverseStr(char *head, char *tail)
{
	char copy = '\0';
	
	for ( ; head < tail; ++head, --tail)
	{
		copy = *head;
		*head = *tail;
		*tail = copy;
	}
}

