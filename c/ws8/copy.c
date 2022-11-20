#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_CHARACTER_TO_HOLD_INT 10

typedef void(*add_ten)(void **data, int num);
typedef void(*printmember_t)(void* data);

typedef struct mix_data 
{
	void *data;
	add_ten addto;
	printmember_t printit;
}element_t;


void AddToInt(void **data, int num);
void AddToFloat(void **data, int num);
void AddToString(void **data, int num);


void PrintInt(void *data);
void PrintFloat(void *data);
void PrintString(void *data);

void AddNumToArrayElement(element_t *mix_data_array, size_t size, int num);
void PrintElement(element_t *mix_data_array, size_t size);

void InitStringElement(element_t *mix_data_array, char *string_to_init, int element_index);
void InitIntElement(element_t *mix_data_array, int init_val, int element_index);
void InitFloatElement(element_t *mix_data_array, float init_val, int element_index);

int main(void)
{

	char str_to_init [] = "chapter";
	float a = 4.2;
	float b = 6.7;
	int c = 12;
	float d = 56.32;
	
	element_t arr_of_mix_data[5];

	InitFloatElement(arr_of_mix_data, a, 0);
	InitFloatElement(arr_of_mix_data, b, 1);
	
	
	arr_of_mix_data[2].data = (char *)malloc(8 *sizeof(char ));
	InitStringElement(arr_of_mix_data, str_to_init, 2);
	
	InitIntElement(arr_of_mix_data, c, 3);
	InitFloatElement(arr_of_mix_data, d, 4);

	AddNumToArrayElement(arr_of_mix_data, 5, 10);
	PrintElement(arr_of_mix_data, 5);
	
	free(arr_of_mix_data[2].data);
	
	return (0);
}

void InitStringElement(element_t *mix_data_array, char *string_to_init, int element_index)
{
	strcpy(mix_data_array[element_index].data, string_to_init);
	mix_data_array[element_index].addto = &AddToString;
	mix_data_array[element_index].printit = &PrintString;
}

void InitIntElement(element_t *mix_data_array, int init_val, int element_index)
{
	mix_data_array[element_index].data = malloc(sizeof(int));
	*((int *)(mix_data_array[element_index].data)) = init_val;
	mix_data_array[element_index].addto = &AddToString;
	mix_data_array[element_index].printit = &PrintString;
}

void InitFloatElement(element_t *mix_data_array, float init_val, int element_index)
{
	mix_data_array[element_index].data = malloc(sizeof(float));
	*((float *)(mix_data_array[element_index].data)) = init_val;
	mix_data_array[element_index].addto = &AddToString;
	mix_data_array[element_index].printit = &PrintString;
}


void AddToInt(void **data, int num)
{
	*((int*)*data) += num;
}

void AddToFloat(void **data, int num)
{
	*((float *)*data) =(*(float *)data) + (float)num;
}

void AddToString(void **data, int num)
{
	char to_add[MAX_CHARACTER_TO_HOLD_INT] = {'\0'};
	size_t length_to_add_realloc = 0; 
	size_t length_of_prev_string = strlen((char *)data);
	void *copy_of_data = NULL;
	assert(NULL != data );
	
	sprintf(to_add, "%d", num); /* converting the number to string */
	length_to_add_realloc = strlen(to_add);	
	copy_of_data = realloc(*data, length_of_prev_string + length_to_add_realloc);
	
	*data = copy_of_data;
	strcat(*data, to_add);
	
}

void PrintInt(void *data)
{
	printf("%d\n", (*(int *)data));
}

void PrintFloat(void *data)
{
	printf("%f\n", (*(float*)data));
}

void PrintString(void *data)
{
	printf("%s\n", (char *)data);
}

void AddNumToArrayElement(element_t *mix_data_array, size_t size, int num)
{
	size_t i = 0;
	
	for ( ; i < size; ++i)
	{
		mix_data_array[i].addto(mix_data_array[i].data, num);
	}
}

void PrintElement(element_t *mix_data_array, size_t size)
{
	size_t i = 0;
	for ( ; i < size; ++i)
	{
		mix_data_array[i].printit(mix_data_array[i].data);
	}
}


void CleanUpElements(element_t *mix_data_array, size_t size)
{
	size_t i = 0;
	
	for ( ; i < size; ++i)
	{
		mix_data_array[i].data = NULL;
	}
}
