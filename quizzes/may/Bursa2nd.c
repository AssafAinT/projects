#include <stdio.h>

int Bursa(int *item_val, size_t size);

static struct bursa
{
	int buy;
	int sell;
	int profit;
}best_op, curr_op;

int main(void)
{
	int item_val_per_hour[]={0,122,0,0,0,400,0};
	size_t arr_size = sizeof(item_val_per_hour)/sizeof(item_val_per_hour[0]);

	Bursa(item_val_per_hour, arr_size);
	printf("to buy in the %d hour\n", best_op.buy + 1);
	printf("to sell in the %d hour\n", best_op.sell + 1);
	printf("your profit is profit %d\n", best_op.profit);
	
	return (0);
}


int Bursa(int *item_val, size_t size)
{
	size_t i = 0;	
	best_op.buy = 0;
	best_op.sell = 0;
	best_op.profit= 0;
	
	curr_op.buy = 0;
	curr_op.sell = 0;
	curr_op.profit= 0;
		
		
	if (size <=1)
	{
		return (0);
	}
	
	for (i = 1; i< size; ++i)
	{
		curr_op.profit = item_val[i] - item_val[curr_op.buy];
		if(curr_op.profit > best_op.profit)
		{
			best_op.buy = curr_op.buy;
			best_op.sell = curr_op.sell;
			best_op.profit= curr_op.profit;	
		}
		else if(item_val[i] < item_val[curr_op.buy])
		{
			curr_op.buy = i;
		}
		curr_op.sell = i;
	}
	

	return (0);
}
