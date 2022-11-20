/************************************************************
*  Author: Eitan Akrish                                     *
*  Date: 22.7.22                                            *
*  Utilities: Helpful utilities for Lab.                    *
*************************************************************/

#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#include "utils.h" /*Utility Header*/

status_ty TestMSwap(void);
status_ty TestSwap(void);
status_ty TestFail(void);
status_ty TestBool(void);

int main()
{
	status_ty status = SUCCESS;
	status_ty expected_stat = FAIL;

	TestMSwap();
	TestSwap();
	status = TestFail();
	UPrintTest(STATUS, "TEST FAIL", &expected_stat, &status);
	TestBool();
	UPrintTest(ERROR_COUNT, NULL, NULL, NULL);

	return 0;
}

status_ty TestMSwap(void)
{
	int a = 10;
	int b = 5;
	int expected = 5;
	status_ty expected_stat = SUCCESS;

	status_ty status = UMSwap(&a, &b, sizeof(int));
	UPrintTest(INT, "MSwap a", &expected, &a);
	expected = 10;
	UPrintTest(INT, "Swapi b", &expected, &b);
	UPrintTest(STATUS, "MSwap test", &expected_stat, &status);

	return status;
}

status_ty TestSwap(void)
{
	int a = 10;
	int b = 5;
	int expected = 5;
	status_ty status = SUCCESS;

	USwap(&a, &b, sizeof(int));
	UPrintTest(INT, "Swap a", &expected, &a);
	expected = 10;
	UPrintTest(INT, "Swapi b", &expected, &b);

	return status;
}

status_ty TestFail(void)
{
	int a = 10;
	int expected = 5;

	status_ty status = UPrintTest(INT, "Should fail", &expected, &a);

	return status;
}

status_ty TestBool(void)
{
	bool_ty is_true = TRUE;
	bool_ty is_false = FALSE;

	UPrintTest(BOOL, "BoolTest", &is_true, &is_true);
	UPrintTest(BOOL, "BoolTest FAil", &is_false, &is_true);

	return SUCCESS;
}
