#include <stdio.h>
#include <stddef.h>

void SumOfRows(int two_d_arr[][3], int result_arr[], int row, int col);

int main()
{
	int row = 2;
	int col = 3;
	size_t i = 0;
	int res[2] = {0, 0};
	int two_d_arr1[2][3] = {{1,2,3} , {4,5,6}};
	
	SumOfRows(two_d_arr1, res, row, col);
		
	return (0);
}

void SumOfRows(int two_d_arr[][3], int result_arr[], int row, int col)
{
	size_t i = 0;
	size_t j = 0;
	
	for (i = 0 ; i<row ; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			result_arr[i] += two_d_arr[i][j];
			
		}
		printf("\nthe result[%ld] element is %d\n", i, result_arr[i]);  
	}
	
}

