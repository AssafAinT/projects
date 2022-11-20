#include <stdio.h>

extern const int ROW = 3;
extern const int COL = 3;

void InterPrint(int arr[ROW][COL]);

int main ()
{
	int arr1[3][3] = {{1,2,3} , {4,5,6}, {7,8,9}};
	InterPrint(arr1);
	
	return (0);
}

void InterPrint(int arr[ROW][COL])
{
	size_t i = 0;
	size_t j = 0;
	
	for (i = 0; i< ROW; ++i)
	{
		for (j=0; i < COL; j++)
		{
			printf("%d ", arr[i][j]);
		}
	}
}

