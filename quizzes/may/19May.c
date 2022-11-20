#include <stdio.h>
#include <stddef.h>

#define STOCK_HOURS 8
int BursaProblem(int *stock, size_t size);

static struct bursa 
{
	int sell;
	int buy;
	int profit;
}current_option, best_option;


int main()
{
	int stock[STOCK_HOURS] = {4,12,3,5,1,4,9,2};
	BursaProblem(stock, STOCK_HOURS);
	
	printf("buy %d\n", best_option.buy);
	printf("sell %d\n", best_option.sell);
	printf("profit %d\n", best_option.profit);
	return (0);
}

int BursaProblem(int *stock, size_t size)
{
	size_t i = 0 ;
	current_option.sell = 0;
	current_option.buy = 0;
	current_option.profit = 0;
	
	best_option.sell = 0;
	best_option.buy = 0;
	best_option.profit = 0;
	
	for (i = 0; i<size-1; i++)
	{
		if(stock[i] > stock[current_option.sell])
		{
			current_option.sell = i;
		}
		else if (stock[i] < stock[current_option.buy])
		{

			if(best_option.profit < stock[current_option.sell]-stock[current_option.buy])
			{
				best_option.buy = current_option.buy;
				best_option.sell = current_option.sell;
				best_option.profit = stock[best_option.sell]-stock[best_option.buy];
			}		
			current_option.buy = i;
			current_option.sell = i;
		}
	}
	
	if(best_option.profit < stock[current_option.sell]-stock[current_option.buy])
	{
		best_option.buy = current_option.buy;
		best_option.sell = current_option.sell;
		best_option.profit = stock[best_option.sell]-stock[best_option.buy];
	}
	
	return (0);
}
