/*****************************************************
 * WS10                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester shpoker                           *
 * today's worksheet is about implementing atoi,itoa *
 * functions and creating a function for finding     *
 * appearnce of character that match in 2 out of 3   *
 * given arrays                                      *
 *                                                   *
 *****************************************************/


#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* atoi */

/*********************Creating enum for exit status****************************/
typedef enum
{
	SUCCESS = 0,
	FAIL = 1,
	ATOI_TEST_SUCCESS = 2,
	ATOI_TEST_FAIL = 3
}status_t;

static status_t exit_status;

/******************************MACROS defining*********************************/
#define BASE_TEN 10
#define BIGGEST_MUDULO_TEN_REMAINDER 9
#define ZERO_CHARACTER 48
#define MINUS_CHARACTER 45
#define ASCII_OF_a 97
#define IS_IN_2_FIRST_ARRAYS 2
#define SIZE_OF_ASCII_TABLE 256

/* macro that converts a given number to char and by the its stored we know if 
 it is a little endian or big endian */
#define IS_LITTLE_ENDIAN  ((char)0x87654321 != 0x21 ? FAIL : SUCCESS)

/****************************Functions Declarations****************************/

/*converts the string argument str to an integer****/
int AtoI(const char *string);
/*coverts the integer num into a character string***/
char *ItoA(int num, char *buffer, int radix);
/*Auxilary function for implementing ItoA***********/
void ReverseStr(char *start, char *end);
/*test template function for AtoI*******************/
status_t TestForAtoI(const char *string);
/*sending test with edge cases to TestForAtoI ******/
status_t CallAtoITestFunctions();
/*function to determine wether the system endianness*/
int IsLittleEndian();
/*prints the latters that appear in both first 2 arrays but not in the third */
void FoundInTwo(char *string1, char *string2, char *string3);

/********************************Beginning of main ****************************/
int main(void)
{
	int num_to_ascii = -1234123; 
	char buffer[11] = "";
	exit_status = SUCCESS;
	
	ItoA(num_to_ascii, buffer, 10);
	
	FoundInTwo("abclid", "aaaaaaaaaaaaaaaaaaaaaelfigd", "hijk");
	
	exit_status = CallAtoITestFunctions();
	if (IS_LITTLE_ENDIAN)
	{
		puts("big endian");
	}
	else
	{
		puts("little endian");
	}
	puts(buffer);
	
	printf("%d\n", IsLittleEndian());
	return (exit_status);
}


/*********************************Functions Definitions************************/

int AtoI(const char *string)
{
	int result = 0;
	int sign = 1;
	if (ZERO_CHARACTER == *string)
	{
		return (result);
	}
	if (MINUS_CHARACTER == *string)
	{
		sign = -1;
		++string;
	}
	for ( ; ('\0' != *string) && ('0' <= *string && '9' >= *string); ++string)
	{
		result = (result * BASE_TEN) + (*string - ZERO_CHARACTER);
	}
	return (sign * result);
}

char *ItoA(int num, char *buffer, int radix)
{
	int remainder_of_num = 0;
	char *copy_of_buffer = buffer;
	char *end_of_buffer = buffer;
	
	if (0 == num)
	{
		*buffer = '0';
		++buffer;
		*buffer = '\0';
		return (--buffer);
	}
	
	if (0 > num )
	{
		if( BASE_TEN == radix)
		{
			*copy_of_buffer = '-';
			++copy_of_buffer;
			++end_of_buffer;
		
		}
		num = -num;
	}
	
	while (num)
	{
		remainder_of_num = num % radix;
		if (BIGGEST_MUDULO_TEN_REMAINDER < remainder_of_num)
		{
			*end_of_buffer = (remainder_of_num - 10) + ASCII_OF_a;
		}
		else
		{
			*end_of_buffer = (remainder_of_num + ZERO_CHARACTER);
		}
		num /= radix;
		++end_of_buffer;
	}
	
	
	--end_of_buffer;
	
	ReverseStr(copy_of_buffer, end_of_buffer);
	
	return (buffer);
}


void ReverseStr(char *start_of_string, char *end_of_string)
{

	char copy_of_string = '\0';
	
	assert( NULL != start_of_string); 
	assert( NULL != end_of_string);
	
	while ( start_of_string < end_of_string )
	{
		copy_of_string = *start_of_string;
		*start_of_string = *end_of_string;
		*end_of_string = copy_of_string;
		
		--end_of_string;
		++start_of_string;
	}
	
}
status_t CallAtoITestFunctions()
{
	exit_status =ATOI_TEST_SUCCESS;
	
	exit_status = TestForAtoI("-12/030");
	if (ATOI_TEST_SUCCESS != exit_status)
	{
		return (exit_status);
	}
	exit_status = TestForAtoI("12/3/5/3441");
	if (ATOI_TEST_SUCCESS != exit_status)
	{
		return (exit_status);
	}
	exit_status = TestForAtoI(".");
	if (ATOI_TEST_SUCCESS != exit_status)
	{
		return (exit_status);
	}	
	exit_status = TestForAtoI("\12?");
	if (ATOI_TEST_SUCCESS != exit_status)
	{
		return (exit_status);
	}
	exit_status = TestForAtoI("0");
	if (ATOI_TEST_SUCCESS != exit_status)
	{
		return (exit_status);
	}
	return exit_status;
}

status_t TestForAtoI(const char *string)
{
	if ( AtoI(string) != atoi(string))
	{
		return (ATOI_TEST_FAIL);
	}
	return (ATOI_TEST_SUCCESS);
}

int IsLittleEndian()
{
	unsigned int to_check = 0x87654321;
	char check = (char ) to_check;     /* determine the storing method */
	
	if (check == 0x21)
	{
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

void FoundInTwo(char *string1, char *string2, char *string3)
{
	unsigned char auxilary_arr[SIZE_OF_ASCII_TABLE]={'\0'};
	unsigned int  i = 0 ;
	
	for ( ; '\0' != *string1; ++string1)
	{
		auxilary_arr[((int)*string1)] = 1;           /* flags the ascii index */
	}
	
	for ( ; '\0' != *string2; ++string2)
	{
		if (1 == auxilary_arr[((int)*string2)] )
		{	
		/* incrementing the index in case there are more than one occurnce */
			auxilary_arr[((int)*string2)] += 1; 
		}
	}
	
	for ( ; '\0' != *string3; ++string3)
	{
		/* in case the letter is also in the third array we disable it ****/
		auxilary_arr[((int)*string3)] = 0;
	}
	
	for ( ; SIZE_OF_ASCII_TABLE != i; ++i)
	{
		if ( IS_IN_2_FIRST_ARRAYS <= auxilary_arr[i])
		{
			printf("%c", i);
		}
	}
	printf("\n");
}



