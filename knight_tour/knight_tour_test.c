/****************************************************
* knight_tour                                       *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 12.08.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "knight_tour.h"

int main(void)
{
    size_t i = 0;
    size_t j = 0;
    unsigned char result[64]= {0};
    unsigned char wandorff_result[64]= {0};
    assert(SUCCESS == KnightTour(0, result, FALSE));
    while (i != 64)
    {
        printf("[%ld]: %d\n", i, result[i]);
        ++i;
    }

    assert(SUCCESS == KnightTour(20, wandorff_result, TRUE));
    while (j != 64)
    {
        printf("[%ld]: %d\n", j, wandorff_result[j]);
        ++j;
    }
    assert(SUCCESS == KnightTour(0, wandorff_result, TRUE));
    j = 0;
    while (j != 64)
    {
        printf("[%ld]: %d\n", j, wandorff_result[j]);
        ++j;
    }
    return (0);

    return (0);
}
