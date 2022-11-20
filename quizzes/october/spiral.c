/****************************************************
* spiral                                            *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

const int row = 4;
const int col = 5;
void PrintMatrixSpiral(int mat[][col], size_t row, size_t col);
int main(void)
{
    int mat[][5] = {{1, 2, 3, 4, 5},
                    {6, 7 ,8, 9 , 10},
                    {11, 12, 13, 14, 15},
                    {16, 17 ,18, 19, 20}};
    
    PrintMatrixSpiral(mat, row, col);
    return (0);
}

void PrintMatrixSpiral(int mat[][col], size_t row, size_t col)
{
    int top = 0;
    int bottom = row -1;
    int left = 0;
    int right = col -1;
    int i = 0;

    while (left <= right && top <= bottom)
    {
        for (i = left; i <= right; ++i)
        {
            printf("%d ", mat[top][i]);
        }
        ++top;
        for(i = top; i <= bottom; ++i)
        {
            printf("%d ", mat[i][right]);
        }
        --right;
        if (top <= bottom)
        {
            for(i = right; i >= left; --i)
            {
                printf("%d ", mat[bottom][i]);
            }
        --bottom;
        }
        if (left <= right)
        {
            for(i = bottom; i >= top; --i)
            {
                printf("%d ", mat[i][left]);
            }
        ++left;
        }
    }   
    printf("\n");

}