/************************************************************
*  Author: Eitan Akrish                                     *
*  Date: 22.7.22                                            *
*  Utilities: Helpful utilities for Lab.                    *
*************************************************************/

#ifndef __ILRD_OL127_128_UTILITIES_H__
#define __ILRD_OL127_128_UTILITIES_H__

#include <stddef.h> /* size_t */

/*fonts color*/
#define FBLACK      "\033[0;30m"
#define FRED        "\033[0;31m"
#define FGREEN      "\033[0;32m"
#define FYELLOW     "\033[0;33m"
#define FBLUE       "\033[0;34m"
#define FPURPLE     "\033[0;35m"
#define FCYAN       "\033[0;36m"
#define FWHITE      "\033[0;37m"
/*fonts color BOLD*/
#define FBBLACK      "\033[1;30m"
#define FBRED        "\033[1;31m"
#define FBGREEN      "\033[1;32m"
#define FBYELLOW     "\033[1;33m"
#define FBBLUE       "\033[1;34m"
#define FBPURPLE     "\033[1;35m"
#define FBCYAN       "\033[1;36m"
#define FBWHITE      "\033[1;37m"

/*end color*/
#define CNONE        "\033[0m"
typedef enum {
    SUCCESS        = 0, 
    FAIL           = 1,
	MALLOC_FAILURE = 2
} status_ty;

typedef enum {
    FALSE = 0, 
    TRUE  = 1
} bool_ty;

typedef enum {
    INT = 0, 
    SIZE_T  = 1,
	STRING = 3,
	CHAR = 4,
	DOUBLE = 5,
	FLOAT = 6,
	STATUS = 7,
	BOOL = 8,
	ERROR_COUNT = 9
} test_type_ty;


/*
const char *status_colored[3] = {""FBGREEN"SUCCESS"CNONE"", ""FBRED"FAIL"CNONE"", 
												""FBRED"MALLOC_FAILURE"CNONE""};*/
extern const char *status_colored[];

/*const char *bool_colored[2] = {""FBRED"FALSE"CNONE"", ""FBGREEN"TRUE"CNONE""};*/
extern const char *bool_colored[];

typedef int(*cmp_func)(const void *ds_data,
                       const void *user_data,
								void *params);

typedef int(*action_func)(void *data, void *params);

typedef bool_ty (*is_match_func)(const void *ds_data, const void *user_data);

status_ty UMSwap(void *a, void *b, size_t size_of_element);
/* Description: Utility Swap for swapping data with any given size using malloc.
 * NOTICE: areas should not overlap use of memcpy for speed rather then memmove.
* Params: a - Pointer to first location to swap.
* 		  b - Pointer to second location to swap.
* 		  size_of_element - the size of the swapping element in bytes.
* Return value: status of swap with status_ty.
* Success: SUCCESS status_ty.
* Failure: MALLOC_FAILURE if there was a mallocing issue
* Complexity:
* 		Time: O(n). (n being amount of bytes being swapped) 
* 		Space: O(n). (n being amount of bytes being swapped)
*/

void USwap(void *a, void *b, size_t size_of_element);
/* Description: Utility Swap for swapping data with any given size up to 200 bytes.
 * NOTICE: areas should not overlap use of memcpy for speed rather then memmove.
* Params: a - Pointer to first location to swap.
* 		  b - Pointer to second location to swap.
* 		  size_of_element - the size of the swapping element in bytes.
* Complexity:
* 		Time: O(n). (n being amount of bytes being swapped) 
* 		Space: O(n). (n being amount of bytes being swapped)
*/

status_ty UPrintTest(test_type_ty type, char *test_name, 
									void *expected_res, void *found_res);
/* Description: Print a result of test and test counts the number of errors.
* Params: type - The test_type enum flag for type of data.
* 		  test_name - a name to be prited to identify the test can be NULL.
* 		  expected_res - a pointer to the expected outcome of the size specified in type.
* Return value: status of test with status_ty.
* Success: SUCCESS status_ty.
* Failure: FAIL if the test Failed.
* Complexity:
* 		Time: O(1).
* 		Space: O(1).
*/

#endif /* __ILRD_OL127_128_UTILITIES_H__ */
