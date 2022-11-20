#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include <string.h> /*strcmp, memcpy*/
#include "utils.h" /*Utility Header*/

#define BUFFER_MAX_SIZE 200

static status_ty PrintTestInt(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestSize_t(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestSize_t(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestString(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestChar(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestDouble(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestFloat(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestStatus(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);
static status_ty PrintTestBool(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter);

const char *status_colored[3] = {""FBGREEN"SUCCESS"CNONE"", ""FBRED"FAIL"CNONE"", 
															""FBRED"MALLOC_FAILURE"CNONE""};
const char *bool_colored[2] = {""FBRED"FALSE"CNONE"", ""FBGREEN"TRUE"CNONE""};

status_ty UMSwap(void *a, void *b, size_t size_of_element)
{
	void *buffer = NULL;

	assert(NULL != a);
	assert(NULL != b);
	assert(0 != size_of_element);
	
	buffer = malloc(size_of_element);

	if (NULL == buffer)
	{
		return MALLOC_FAILURE;
	}
	
	memcpy(buffer, a, size_of_element);
	memcpy(a, b, size_of_element);
	memcpy(b, buffer, size_of_element);

	free(buffer);
	buffer = NULL;

	return SUCCESS;
}

void USwap(void *a, void *b, size_t size_of_element)
{
	char buffer[BUFFER_MAX_SIZE] = {0};

	assert(NULL != a);
	assert(NULL != b);
	assert(0 != size_of_element);
	
	memcpy(buffer, a, size_of_element);
	memcpy(a, b, size_of_element);
	memcpy(b, buffer, size_of_element);

	return;
}

status_ty UPrintTest(test_type_ty type, char *test_name, 
									void *expected_res, void *found_res)
{
	static size_t error_counter = 0;
	void *fake = NULL;

	if (NULL == expected_res)
	{
		expected_res = fake;
	}

	if (NULL == found_res)
	{
		found_res = fake;
	}

	if (NULL == test_name)
	{
		test_name = "Not Named";
	}

	switch (type)
	{
		case INT:
			return PrintTestInt(test_name, expected_res, found_res, &error_counter);
			break;

		case SIZE_T:
			return PrintTestSize_t(test_name, expected_res, found_res, &error_counter);
			break;

		case STRING:
			return PrintTestString(test_name, expected_res, found_res, &error_counter);
			break;

		case CHAR:
			return PrintTestChar(test_name, expected_res, found_res, &error_counter);
			break;

		case DOUBLE:
			return PrintTestDouble(test_name, expected_res, found_res, &error_counter);
			break;

		case FLOAT:
			return PrintTestFloat(test_name, expected_res, found_res, &error_counter);
			break;

		case STATUS:
			return PrintTestStatus(test_name, expected_res, found_res, &error_counter);
			break;

		case BOOL:
			return PrintTestBool(test_name, expected_res, found_res, &error_counter);
			break;

		case ERROR_COUNT:
			printf("\nTotal Num of "FRED"ERRORS"CNONE": %ld\n\n", error_counter);
			return SUCCESS;
			break;

		default:
			printf("\n\n"FBRED"THIS TYPE HAS NOT BEEN ADDED YET, PLEASE TALK TO EITAN AKRISH."CNONE"\n\n");
			return FAIL;
			break;
	}
}

static status_ty PrintTestInt(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	int exp = *(int *)expected_res;
	int found = *(int *)found_res;
	status_ty outcome = !!(exp - found);

	printf("\n%s: %s\nExpected: %d\nFound: %d\n", status_colored[outcome], test_name,
																	exp, found);
	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

static status_ty PrintTestSize_t(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	size_t exp = *(size_t *)expected_res;
	size_t found = *(size_t *)found_res;
	status_ty outcome = !!(exp - found);

	printf("\n%s: %s\nExpected: %ld\nFound: %ld\n", status_colored[outcome], test_name,
																	exp, found);
	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

static status_ty PrintTestString(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	char *exp = (char *)expected_res;
	char *found = (char *)found_res;
	status_ty outcome = !!(strcmp(exp, found));

	printf("\n%s: %s\nExpected: %s\nFound: %s\n", status_colored[outcome], test_name,
																	exp, found);
	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

static status_ty PrintTestChar(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	char exp = *(char *)expected_res;
	char found = *(char *)found_res;
	status_ty outcome = !!(exp - found);

	printf("\n%s: %s\nExpected: %c\nFound: %c\n", status_colored[outcome], test_name,
																	exp, found);
	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

static status_ty PrintTestDouble(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	double exp = *(double *)expected_res;
	double found = *(double *)found_res;
	status_ty outcome = !!(exp - found);

	printf("\n%s: %s\nExpected: %f\nFound: %f\n", status_colored[outcome], test_name,
																	exp, found);
	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

static status_ty PrintTestFloat(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	float exp = *(float *)expected_res;
	float found = *(float *)found_res;
	status_ty outcome = !!(exp - found);

	printf("\n%s: %s\nExpected: %f\nFound: %f\n", status_colored[outcome], test_name,
																	exp, found);
	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

static status_ty PrintTestStatus(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	status_ty exp = *(status_ty *)expected_res;
	status_ty found = *(status_ty *)found_res;
	status_ty outcome = !!(exp - found);

	printf("\n%s: %s\nExpected: %s\nFound: %s\n", status_colored[outcome], test_name,
									status_colored[exp], status_colored[found]);

	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

static status_ty PrintTestBool(char *test_name, void *expected_res, 
								void *found_res, size_t *error_counter)
{
	bool_ty exp = *(bool_ty *)expected_res;
	bool_ty found = *(bool_ty *)found_res;
	status_ty outcome = !(exp == found);

	printf("\n%s: %s\nExpected: %s\nFound: %s\n", status_colored[outcome], test_name,
										bool_colored[exp], bool_colored[found]);

	if (FAIL == outcome)
	{
		printf("ERROR NUM: %ld\n", ++*error_counter);
	}

	return outcome;
}

