/****************************************************
* find_pattern                                      *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void FindPatternInText(char *pattern, char *text);
int main(void)
{
    FindPatternInText("pa","pattern"); 
    FindPatternInText("TEXT", "THIS IS A TEXT ABOUT TEST OF TEXT");


    return (0);
}
void FindPatternInText(char *pattern, char *text)
{
    char *pattern_runner = text;

    pattern_runner = strstr(pattern_runner, pattern);
    while (NULL != pattern_runner)
    {
        printf("the pattern is found in %ld\n",
                pattern_runner- text);
        ++pattern_runner;
        pattern_runner = strstr(pattern_runner, pattern);
    }
}