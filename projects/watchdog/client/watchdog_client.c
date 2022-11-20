/****************************************************
* Watchdog                                          *
* Assaf Ainhoren                                    *
* Reviewer: Haggai Newman                           *
* date: 31.08.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include "watchdog.h"

#define UNUSED(x) (void)x

int main(int argc, char *argv[])
{
    int x = 12;
    int ret_val = 0;
    UNUSED(argc);

    while (x > 8)
    {
        sleep(2);
        --x;
    }
    ret_val = MakeMeImmortal(2, 2, argv[0]);
    if(SUCCESSED != ret_val)
    {
        printf("MakeMeImmortal failed becuase ret_Val is: %d\n", ret_val);
        LetMeDie();    
    }
    if (-1 == write(1, "done one loop\n", 15))
    {
        return 1;
    }
    while (x > 1)
    {
        sleep(20);
        --x;
    }
    /*printf("this is arg[2] %s\n", argv[2]);*/
    LetMeDie();
    sleep(10);
    printf("that was fun, lets start cpp please\n");

    x =30;
    MakeMeImmortal(2, 2, argv[0]);
    if (-1 == write(1, "done one loop\n", 15))
    {
        return 1;
    }
    while (x > 1)
    {
        sleep(20);
        --x;
    }
    /*printf("this is arg[2] %s\n", argv[2]);*/
    LetMeDie();
    sleep(10);
    printf("that was fun, lets start cpp please\n");
    return (0);
}
