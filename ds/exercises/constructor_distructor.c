/****************************************************
* constructorDistructor                             *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void __attribute__((constructor)) CalledFirst(void);
void __attribute__((destructor)) CalledLast(void);

int main(void)
{
    puts("I am The Main Program");
    return (0);
}
void CalledFirst(void)
{
    puts("I am The First Program");
}
void CalledLast(void)
{
    puts("I am The Last Program");
}
