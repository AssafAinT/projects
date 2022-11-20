/****************************************************
* huff                                              *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define ASCII_TABLE_SIZE 256
#define SIZE_T_MAX 0XFFFFFFFF
#define UNUSED(x) (void)x

void CountApper(const char *file_name, size_t char_lut[ASCII_TABLE_SIZE]);
size_t CountDifferentTypeOfChar(size_t *char_lut);
void SortLut(size_t char_lut[ASCII_TABLE_SIZE]);
static void ValSwap(size_t *first_num, size_t *second_num);
void BubbleSort(size_t *arr, size_t arr_size);
void PushInfoToBinaryFile(size_t number_of_characters,
                          size_t char_lut[ASCII_TABLE_SIZE]);
int main(int argc, char **argv)
{
    size_t char_appearence[ASCII_TABLE_SIZE] = {0};
    size_t total_characters = 0; /* every character not 0 */
    /* after counting write in the file every character and apperance in bit */
    
    CountApper(argv[1], char_appearence);
    total_characters = CountDifferentTypeOfChar(char_appearence);
    printf("total_characters = %ld\n", total_characters);
   /* SortLut(char_appearence);*/
    PushInfoToBinaryFile(total_characters, char_appearence);
    UNUSED(argc);
    return (0);
}

void CountApper(const char *file_name, size_t char_lut[ASCII_TABLE_SIZE])
{
    unsigned char ch = '\0';
    FILE *file = fopen(file_name, "r");
    while (!feof(file))
	{
		ch = fgetc(file);
        ++char_lut[ch];
        printf("%ld in char_lut[%c]\n", char_lut[ch], ch);
	}
    fclose(file);
}

size_t CountDifferentTypeOfChar(size_t *char_lut)
{
    size_t counter = 0;
    size_t runner = 0;
    for ( ; runner < ASCII_TABLE_SIZE; ++runner)
    {
        if (char_lut[runner] != 0)
        {
           ++counter;
        }
    }
    return (--counter);
}

void SortLut(size_t char_lut[ASCII_TABLE_SIZE])
{
    BubbleSort(char_lut, ASCII_TABLE_SIZE); 
}

static void ValSwap(size_t *first_num, size_t *second_num)
{
	size_t temp = *first_num;
	*first_num = *second_num;
	*second_num = temp;
	
}

void BubbleSort(size_t *arr, size_t arr_size)
{
	size_t i = 0; 
	size_t k = 0;
	int is_sorted = 0;

	assert(NULL != arr);
	
	for ( ;i < arr_size && !is_sorted; ++i)
	{
		is_sorted = 1;
		for ( k = 0 ; k < (arr_size - i - 1); ++k)
		{
            if (arr[k] >
                arr[k + 1])
            {
                ValSwap(&arr[k] , &arr[k + 1]);
                is_sorted = 0;
            }
        }
	}

}

void PushInfoToBinaryFile(size_t number_of_characters, size_t char_lut[ASCII_TABLE_SIZE])
{
    unsigned char ch = '\0';
    FILE *file = fopen("histograma.b", "wb");
    size_t counter = 0;
    size_t runner = 0;
    fprintf(file, "%ld", number_of_characters);    
    for ( ; runner < ASCII_TABLE_SIZE; ++runner)
    {
        if (char_lut[runner] != 0)
        {
            fprintf(file, "%c", ch);
            fprintf(file, "%ld", (char_lut[runner]));
        }
    }

    fclose(file);   
}