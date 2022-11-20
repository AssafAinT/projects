/****************************************************
* Flipimage                                         *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void FlipNonNaiveImage(int mat[3][3], size_t size);
void Flipimage90Degrees(int mat[3][3], size_t size);
void PrintArray(int mat[3][3], size_t size);
int main(void)
{
    int matrix[3][3] = {{1, 2, 1} , {4, 5, 7}, { 8, 0 ,1}};
    PrintArray(matrix, 3);
    Flipimage90Degrees(matrix, 3);

    FlipNonNaiveImage(matrix, 3);
    PrintArray(matrix, 3);
    return (0);
}

void Flipimage90Degrees(int mat[3][3], size_t size)
{
    size_t col = 0;
    int row = size -1;

    for ( ; col < size; ++col)
    {
        for (row = size; row > 0; --row)
        {
            printf("%d ", mat[row -1][col]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void FlipNonNaiveImage(int mat[3][3], size_t size)
{
    long int i = 0;
    long int j = 0;
    int temp = 0;
    size_t runner_size = size -1;
    /* for moving half diagonal */
    for ( ; j < size/2  ; ++j)
    {
        for (i = j; i < (size - 1 -j); ++i)
        {
            size_t row_swapper = runner_size -i;
            size_t col_swapper = runner_size -j;
            temp = mat[j][i];
            
            mat[j][i] = mat[row_swapper][j];
            mat[row_swapper][j] = mat[col_swapper][row_swapper];
            mat[col_swapper][row_swapper] = mat[i][col_swapper];
            mat[i][col_swapper] = temp;
        }
    }

}

void PrintArray(int mat[3][3], size_t size)
{
    long int row = 0;
    long int col = 0;

    for ( ; row < size; ++row)
    {
        for (col = 0; col < size; ++col)
        {
            printf("%d ", mat[row][col]);
        }
        printf("\n");
    }

    printf("\n\n\n");
}