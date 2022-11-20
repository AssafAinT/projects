#include <stdio.h>

typedef enum
{
    SUM,
    MAX_I,
    MIN_I,
    O_ARR_SIZE
}o_param_ty;
void MaxSubArray(int *src_arr, size_t arr_size, int *o_res_arr);

int main(void)
{
    int array[] = {-2,0,-3,-4,-1,2,3,-5,-4};
	int o_res[O_ARR_SIZE] = {0};
	MaxSubArray(array, 9, o_res);
	
	printf("the min index is %d\n", o_res[MIN_I]);
	printf("the max index is %d\n", o_res[MAX_I]);
	printf("the sum is %d\n", o_res[SUM]);
	return (0);
}

void MaxSubArray(int *src_arr, size_t arr_size, int *o_res_arr)
{
    int curr_max[O_ARR_SIZE] = {0};
    size_t i = 0;

    for ( ; i < arr_size; ++i)
    {
        curr_max[SUM] += src_arr[i];
        curr_max[MAX_I] = i;
        
        if (0 > curr_max[SUM])
        {
            curr_max[SUM] = 0;
            curr_max[MIN_I] = curr_max[MAX_I] + 1;
        }

        if (o_res_arr[SUM] < curr_max[SUM])
        {
            o_res_arr[SUM] = curr_max[SUM];
            o_res_arr[MAX_I] = curr_max[MAX_I];
            o_res_arr[MIN_I] = curr_max[MIN_I];
        } 
    }
}