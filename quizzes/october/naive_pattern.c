/****************************************************
* naive_pattern                                     *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
void NaivePattern(char *pattern, char *txt);
int main(void)
{
    char *txt = "ABBACABBA";
    char *pattern = "ABBA";
    NaivePattern(pattern, txt);
    return (0);
}

void NaivePattern(char *pattern, char *txt)
{
    size_t pat_len =  strlen(pattern);
    size_t txt_len = strlen(txt);
    size_t dif = txt_len - pat_len;

    for (size_t i = 0; i <= dif; ++i) 
    {
        size_t j = 0;
        for (; j < pat_len && (txt[i+j] == pattern[j]); ++j)
        {
            /* empty loop */
        }
        if (j == pat_len)
        {
            printf("pattern found at index %d\n", i);
        }
    }
}