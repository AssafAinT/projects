/****************************************************
* string_premutation                                *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <string.h>
static void CharSwap(char *c1, char *c2);
void StringPermutation(char *string);
void RecStringPermutation(char *string, size_t start, size_t end);


int main(void)
{
    char string[] = "ABCD";
    StringPermutation(string);
    return (0);
}

void StringPermutation(char *string)
{
    size_t len = 0;
    assert(NULL != string);
    
    len = strlen(string);

    RecStringPermutation(string, 0, len -1 );
}

void RecStringPermutation(char *string, size_t start, size_t end)
{
    size_t i = 0;

    if (end == start)
    {
        printf("%s\n", string);
        return;
    }
    for (i = start ; i <= end; ++i)
    {
        CharSwap(string + start, string + i);
        RecStringPermutation(string, start + 1, end);
        CharSwap(string + start, string + i);
    }
}
static void CharSwap(char *c1, char *c2)
{
    char temp = '\0';
    temp = *c1;
	*c1 = *c2;
	*c2 = temp;
	
}