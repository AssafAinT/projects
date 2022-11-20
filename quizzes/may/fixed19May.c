#include <stdio.h>
#include <stdio.h>/* printf() */
#include <stdlib.h>/* malloc(), size_t */
int *BursaFunc(int bursa[], size_t size);

static struct bursa 
{
	int sell;
	int buy;
	int profit;
}item;



int main()
{
    int bursa_array[] = {6, 12, 3, 5, 1, 4, 9, 2};
    int *best_option = BursaFunc(bursa_array, 8);
    if(0 < *(best_option + 2))
    {
        printf("the buy index is %d, the sell index is %d, and the profit is %d\n", *best_option, *(best_option + 1), *(best_option + 2));
    }
    else
    {
        printf("No profitable option in the market");
    }

    return 0;
}


int *BursaFunc(int bursa[], size_t size)
{
    size_t i = 0;
    int buy = 0;
    int sell = 0;
    int *option = (int *) malloc(sizeof(int) * 3); /*first element is buy, second element is sell, thirs element is profit*/
    *(option + 2) = 0;
    for(i = 0; size > i; ++i)
    {
        if(bursa[i] < bursa[buy])
        {
            if(bursa[sell] - bursa[buy] >  *(option + 2))
            {
                *option = buy;
                *(option + 1) = sell;
                *(option + 2) = bursa[sell] - bursa[buy];
            }
            buy = i;
            sell = i;
        }
        else if(bursa[i] > bursa[sell])
        {
            sell = i;
        }
    }

    if(bursa[sell] + bursa[buy] >  *(option + 2))
    {
        *option = buy;
        *(option + 1) = sell;
        *(option + 2) = bursa[sell] - bursa[buy];
    }

    return option;
}

