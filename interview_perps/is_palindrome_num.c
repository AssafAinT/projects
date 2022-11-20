/****************************************************
* is_palindrome                                     *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int IsPalindrome(int number);
int ReverseNumber(int number);
int IsStringPalindrome(char *string);
int main(void)
{
    int x = 1331;
    int y = 1332;
    int z = 1001;

    assert(IsPalindrome(x));
    assert(!IsPalindrome(y));
    assert(IsPalindrome(z));
    assert(!IsStringPalindrome("ABBX"));
    assert(IsStringPalindrome("ACBBCA"));
    assert(!IsStringPalindrome("A1C2BBC1A"));
    return (0);
}

int IsPalindrome(int number)
{
    return (number == ReverseNumber(number));
}
int ReverseNumber(int number)
{
    int sign = 1;
    int result = 0;
    
    if (number < 0)
    {
        sign = -1;
    }

    while (0 < number)
    {
        result = (result * 10) + (number % 10);
        number /= 10;
    }

    return (sign * result);
}

int IsStringPalindrome(char *string)
{
    char *end = string + (strlen(string) - 1);

    while (string < end && *string == *end)
    {
        ++string;
        --end;
    }

    return !(*string - *end);
}