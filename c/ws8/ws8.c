/* WS8 
* 30.5.22
* Assaf Ainhoren
* reviewer: Roi Herscho 
* The program holds different data types in a array of struct,prints them and adds numbers to them */

#include <stdio.h> /*printf, sizeof, size_t */
#include <stdlib.h> /* malloc and realloc */
#include <assert.h> /* assert */
#include <string.h> /* strcpy and strlen */

typedef enum 
{
	SUCCESS = 0,
	FAIL_INIT = 1,
	SPRINTF_FAIL = 2,
	REALLOC_FAIL = 3,
	ERROR_IN_MAX2 = 4,
	ERROR_IN_MAX3 = 5,
	ERROR_IN_SIZE_OF_VAR = 6,
	ERROR_IN_SIZE_OF_TYPE = 7
}status_t;

/*  max character to hold biggest positive int */
#define MAX_CHARACTER_TO_HOLD_INT 10

#define THE_NULL_CHARACTER_SIZE 1

/* function like macros */
#define MAX2(a, b)  ((a>b)? a:b)
#define MAX3(a, b, c) ((a > b && (a > c) ? a:(b > c ? b : c)))
#define SIZE_OF_VAR(param)  ((size_t)(&(param)+1)-(size_t)(&(param)))

#define SIZE_OF_TYPE(type, result) do{ \
type x; \
result = SIZE_OF_VAR(x) ; \
}while(0)


/* typdef function pointers */
typedef status_t(*add_num)(void **data, int num);
typedef void(*printmember_t)(void* data);

/* typedef struct that hold various types and can add and print to the data*/
typedef struct mix_data 
{
	void *data;
	add_num addto;
	printmember_t printit;
}element_t;

/* MixTypeArray Exercise */
status_t MixTypeArrayExercise();
/* iterating over the array and sending certain data-type to add-num function */
status_t AddNumToArrayElement(element_t *mix_data_array, size_t size, int num);
/* adds a int (num) to the origina value */
status_t AddToInt(void **data, int num);
/* adds a int (num) to the origina value */
status_t AddToFloat(void **data, int num);
/* adds the int (num) as a string to the original value */
status_t AddToString(void **data, int num);

/* sending the data in the array of struct to the appropriate printing function by thier type  */
void PrintElement(element_t *mix_data_array, size_t size);
/* print elements that holds int values */
void PrintInt(void *data);
/* print elements that holds float values */
void PrintFloat(void *data);
/* print elements that hold strings */
void PrintString(void *data);

/* cleans the array of structs */
void Clean(element_t *mix_data_array, size_t size);

/* test function for the last exercises with like-functio macros */
status_t test_function();



int main(void)
{
	status_t exit_status = SUCCESS;
	
	exit_status = MixTypeArrayExercise();
	
	if(SUCCESS != exit_status)
	{
		return exit_status;
	}
	exit_status = test_function();
	
	if(SUCCESS != exit_status)
	{
		return exit_status;
	}
	
	
	return (SUCCESS);
}


status_t MixTypeArrayExercise()
{
	float first_float = 4.2;
	float second_float = 6.7;
	int first_int = 12;
	float third_float = 56.32;
	
	status_t exit_status = SUCCESS;
	
	element_t arr_of_mix_data[5];
	
	arr_of_mix_data[0].data = &first_float;
	arr_of_mix_data[0].addto = AddToFloat;
	arr_of_mix_data[0].printit = PrintFloat;
	
	arr_of_mix_data[1].data = &second_float;
	arr_of_mix_data[1].addto = AddToFloat;
	arr_of_mix_data[1].printit = PrintFloat;
	
	arr_of_mix_data[2].data =(char *)malloc(8 *sizeof(char ));
	if(NULL == arr_of_mix_data[2].data )
	{
		exit_status = FAIL_INIT;
		return (exit_status);
	}
	if(NULL==strcpy(arr_of_mix_data[2].data, "chapter"))
	{
		free(arr_of_mix_data[2].data);
		exit_status = FAIL_INIT;
		return (exit_status);
	}
	arr_of_mix_data[2].addto = AddToString;
	arr_of_mix_data[2].printit = PrintString;
	
	arr_of_mix_data[3].data = &first_int;
	arr_of_mix_data[3].addto = AddToInt;
	arr_of_mix_data[3].printit =PrintInt;
	
	arr_of_mix_data[4].data = &third_float;
	arr_of_mix_data[4].addto = AddToFloat;
	arr_of_mix_data[4].printit =PrintFloat;

	PrintElement(arr_of_mix_data, 5);
	
	exit_status = AddNumToArrayElement(arr_of_mix_data, 5, 10);
	if (SUCCESS != exit_status)
	{
		return (exit_status);
	}
	
	PrintElement(arr_of_mix_data, 5);
	
	free(arr_of_mix_data[2].data);
	Clean(arr_of_mix_data, 5);
	
	return (exit_status);
}
status_t AddToInt(void **data, int num)
{
	assert(NULL != data );
	
	(*(int *)*data) =(*(int *)*data) + num;
	return SUCCESS;
}

status_t AddToFloat(void **data, int num)
{
	assert(NULL != data );
	
	(*(float *)*data) =(*(float *)*data) + (float)num;
	return SUCCESS;
}

status_t AddToString(void **data, int num)
{
	char to_add[MAX_CHARACTER_TO_HOLD_INT] = {'\0'};
	size_t length_to_add_realloc = 0; 
	size_t length_of_prev_string = strlen((char *)*data);
	char *copy_of_data = NULL;
	
	assert(NULL != data );
	
	if(0>sprintf(to_add, "%d", num))  /* converting the number to string */
	{
		return SPRINTF_FAIL;
	}
	length_to_add_realloc = strlen(to_add);
	copy_of_data = realloc(*data ,(length_of_prev_string+length_to_add_realloc)+THE_NULL_CHARACTER_SIZE);
	if (NULL == copy_of_data)
	{
		return REALLOC_FAIL;
	}

	*data = copy_of_data;
	strcat(*data, to_add);
	
	return SUCCESS;
}

void PrintInt(void *data)
{
	assert(NULL != data );
	
	printf("%d\n", (*(int *)data));
}

void PrintFloat(void *data)
{
	assert(NULL != data );
	
	printf("%f\n", (*(float*)data));
}

void PrintString(void *data)
{
	assert(NULL != data );
	
	printf("%s\n", (char *)data);
}

status_t AddNumToArrayElement(element_t *mix_data_array, size_t size, int num)
{
	size_t i = 0;
	status_t exit_status = SUCCESS;
	
	for ( ; i < size; ++i)
	{
		exit_status = mix_data_array[i].addto(&mix_data_array[i].data, num);
		if(SUCCESS != exit_status)
		{
			return exit_status;
		}
	}
	return (exit_status);
}

void PrintElement(element_t *mix_data_array, size_t size)
{
	size_t i = 0;
	for ( ; i < size; ++i)
	{
		mix_data_array[i].printit(mix_data_array[i].data);
	}
	
}

void Clean(element_t *mix_data_array, size_t size)
{
	size_t i = 0;
	for ( ; i < size; ++i)
	{
		mix_data_array[i].data = NULL;
		mix_data_array[i].addto = NULL;
		mix_data_array[i].printit = NULL;
	}
}

status_t test_function()
{
	size_t result = 0;
	
	float ftest = 12.3;
	char ctest =2;
	int itest = 232124;
	
	if ((sizeof(ftest)) != (SIZE_OF_VAR(ftest)))
	{
		return ERROR_IN_SIZE_OF_VAR;
	}
	if ((sizeof(ctest)) != (SIZE_OF_VAR(ctest)))
	{
		return ERROR_IN_SIZE_OF_VAR;
	}
	if ((sizeof(itest)) != (SIZE_OF_VAR(itest)))
	{
		return ERROR_IN_SIZE_OF_VAR;
	}
	
	SIZE_OF_TYPE(int, result);
	if((sizeof(int)) != (result))
	{
		return ERROR_IN_SIZE_OF_TYPE;
	}
	
	result = 0;
	SIZE_OF_TYPE(char, result);
	if((sizeof(char)) != (result))
	{
		return ERROR_IN_SIZE_OF_TYPE;
	}
	
	if(5 != MAX2(2, 5))
	{
		return ERROR_IN_MAX2;
	}
	
	if(2 != MAX2(1, 2))
	{
		return ERROR_IN_MAX2;
	}
	if(7 != MAX3(2,7,5))
	{
		return ERROR_IN_MAX3;
	}

	return SUCCESS;
}

