/* Name : Maayan Sheraizin, Subject : ws8 structs , Reviewer : */

#include <stdio.h> /*fpr printf, NULL,size_t*/
#include <assert.h> /*for assert*/
#include <stdlib.h> /*for malloc,realloc free*/
#include <string.h> /*for strlen,strcpy,strcat*/
typedef enum 
{
	SUCCESS = 0,
	FAIL_INIT = 1,
	SPRINTF_FAIL = 2,
	REALLOC_FAIL = 3,
	ERROR_IN_MAX2 = 4,
	ERROR_IN_MAX3 = 5,
	ERROR_IN_SIZEOF_VAR = 6,
	ERROR_IN_SIZEOF_TYPE = 7
}exit_status_t;


typedef void (*fptr_print_t)(void *ptr); /* for exe 1*/
typedef exit_status_t (*fptr_add_t)(void **ptr, int num);/* for exe 1*/
typedef void(*fptr_clean_t)(void *ptr); /*for exe_1 clean*/

 
typedef struct
{
	void *var_holder;
	fptr_print_t print_func;
	fptr_add_t add_func;
	fptr_clean_t clean_func;	
}var_types_t;
 
#define INIT_SIZEOF_VAR_TYPE_ARR 5 
#define MAX_NUM_DIGITS_IN_INT 10 /**/



#define MAX2(a, b) (((a) > (b) ) ? (a) : (b)) /*exe5_1:*/
#define MAX3(a, b, c) (MAX2((MAX2((a), (b))), (c))) /*exe5_2:*/
#define SIZEOF_VAR(var) (((size_t)((&(var)) + 1)) - ((size_t)(&(var)))) /*exe 6: */
#define SIZEOF_TYPE(type, result) do{ \
type x; \
result = SIZEOF_VAR(x) ; \
}while(0)
 
 


exit_status_t TestMax2(void);/*exe 5_1-test */
exit_status_t TestMax3(void);/*exe 5_2 -test*/
exit_status_t TestSizeOfVar(void);/*exe 6 -test*/
exit_status_t TestSizeOfType(void);/*exe 7 -test*/

/*functions of exe 1*/
var_types_t *CreatVarTypesArray(void);/*creat the array*/
exit_status_t InitVarTypesArray(var_types_t *var_types_arr);/*init the array*/
exit_status_t InitStringElmnt(var_types_t *var_types_arr, char *str_for_init_arr, int elmnt_indx); /*initialize str_elmnts*/
exit_status_t InitFloatElmnt(var_types_t *var_types_arr, float init_value, int elmnt_indx); /*init float elmnts*/
exit_status_t InitIntElmnt(var_types_t *var_types_arr, int init_value, int elmnt_indx); /*init int elm*/
void FreeVarTypesArr(var_types_t *var_types_arr, size_t last_init_indx); /*free arr*/
void FreeVarHolder(var_types_t *var_types_arr, size_t last_init_indx); /* vargolder member is a pointer to heap */
/*functions for init struct arr used in exe 1 */
void PrintFloat(void *ptr);
void PrintInt(void *ptr);
void PrintString(void *ptr);
exit_status_t AddToFloat(void **ptr, int num);
exit_status_t AddToInt(void **ptr, int num);
exit_status_t AddToString(void **ptr, int num);
void EmptyFunc(void *ptr);/* my types currntly dont need special cleanup*/
/* functions for actions on the arr */
void PrintArrayElements(var_types_t *var_types_arr , size_t size_of_arr); /* print arr members*/
exit_status_t AddToEachArrElemnt(var_types_t *var_types_arr, size_t size_of_arr, int num); /*add num to members */

int main(void)
{	
	
	var_types_t *var_types_arr = NULL; /*for exe 1*/ 
	exit_status_t test_status = SUCCESS; /* for tests of exe 5-7*/
	
	var_types_arr = CreatVarTypesArray();
	test_status = InitVarTypesArray(var_types_arr); /*inialize said array*/
	if (SUCCESS != test_status)
	{
		return test_status;
	}
	PrintArrayElements(var_types_arr,INIT_SIZEOF_VAR_TYPE_ARR);
	test_status = AddToEachArrElemnt(var_types_arr, INIT_SIZEOF_VAR_TYPE_ARR, 16); 
	if (SUCCESS != test_status)
	{
		return test_status;
	}
	PrintArrayElements(var_types_arr,INIT_SIZEOF_VAR_TYPE_ARR); 
	FreeVarTypesArr(var_types_arr ,INIT_SIZEOF_VAR_TYPE_ARR); /* free all */
	
	/*test exe 5*/
	test_status = TestMax2();
	if (SUCCESS !=test_status)
	{
		return test_status;
	}
	
	test_status = TestMax3();
	if (SUCCESS !=test_status)
	{
		return test_status;
	}
	
	/*test SIZEOF_VAR - exe 6*/
	test_status = TestSizeOfVar();
	if (SUCCESS !=test_status)
	{
		return test_status;
	}
	
	/*test SIZEOF_TYPE exe 7 */
	test_status = TestSizeOfType();
	if (SUCCESS !=test_status)
	{
		return test_status;
	} 

	return SUCCESS;
}



var_types_t *CreatVarTypesArray(void)
{
	var_types_t *var_types_arr = (var_types_t*)malloc(INIT_SIZEOF_VAR_TYPE_ARR * sizeof(var_types_t));
	assert(NULL != var_types_arr);
	return var_types_arr;
}

exit_status_t InitVarTypesArray(var_types_t *var_types_arr)
{

	char str_for_init_arr[] ="chapter";
	exit_status_t exit_status = SUCCESS;
	/*init first member */
	exit_status = InitFloatElmnt(var_types_arr, 4.2, 0);
	if (SUCCESS != exit_status)
	{
		return exit_status;
	}
	
	/*init second member*/
	exit_status = InitFloatElmnt(var_types_arr, 6.7, 1);
	if (SUCCESS != exit_status)
	{
		return exit_status;
	}
		
	/*init 3 member*/
	exit_status = InitStringElmnt(var_types_arr, str_for_init_arr, 2);
	if (SUCCESS != exit_status)
	{
		return exit_status;
	}
		
	/*init 4 member*/
	
	exit_status = InitIntElmnt(var_types_arr, 12, 3);
	if (SUCCESS != exit_status)
	{
		return exit_status;
	}
	/*init 5 member */
	exit_status = InitFloatElmnt(var_types_arr, 56.32, 4);
	if (SUCCESS != exit_status)
	{
		return exit_status;
	}
	return SUCCESS;
}	

exit_status_t InitStringElmnt(var_types_t *var_types_arr, char *str_for_init_arr, int elmnt_indx)
{

	var_types_arr[elmnt_indx].var_holder = malloc(strlen(str_for_init_arr)+1);
	if (NULL == var_types_arr[elmnt_indx].var_holder)
	{
		FreeVarTypesArr(var_types_arr, elmnt_indx);
		return FAIL_INIT;
	}
	
	if (NULL == strcpy(var_types_arr[elmnt_indx].var_holder, str_for_init_arr))
	{
	
		FreeVarTypesArr(var_types_arr, elmnt_indx);
		return FAIL_INIT;
	
	}
	var_types_arr[elmnt_indx].print_func = &PrintString;	
	var_types_arr[elmnt_indx].add_func = &AddToString;
	var_types_arr[elmnt_indx].clean_func = &EmptyFunc;/*this type doesnt need any special cleanup*/
	return SUCCESS;
}
exit_status_t InitFloatElmnt(var_types_t *var_types_arr, float init_value, int elmnt_indx)
{

	var_types_arr[elmnt_indx].var_holder = malloc(sizeof(float));
	if (NULL == var_types_arr[elmnt_indx].var_holder)
	{
		FreeVarTypesArr(var_types_arr, elmnt_indx);
		return FAIL_INIT;
	}
	*((float*)(var_types_arr[elmnt_indx].var_holder)) = init_value;
	var_types_arr[elmnt_indx].print_func = &PrintFloat;
	var_types_arr[elmnt_indx].add_func = &AddToFloat;
	var_types_arr[elmnt_indx].clean_func = &EmptyFunc;/*this type doesnt need any special cleanup*/
	return SUCCESS;
}

exit_status_t InitIntElmnt(var_types_t *var_types_arr, int init_value, int elmnt_indx)
{

	var_types_arr[elmnt_indx].var_holder = malloc(sizeof(int));
	if (NULL == var_types_arr[elmnt_indx].var_holder)
	{
		FreeVarTypesArr(var_types_arr, elmnt_indx );
		return FAIL_INIT;
	}
	*((int*)(var_types_arr[elmnt_indx].var_holder)) = init_value;
	var_types_arr[elmnt_indx].print_func = &PrintInt;
	var_types_arr[elmnt_indx].add_func = &AddToInt;
	var_types_arr[elmnt_indx].clean_func = &EmptyFunc;/*this type doesnt need any special cleanup*/
	return SUCCESS;
}

void PrintFloat(void *ptr)
{
	printf("%f\n",*((float*)ptr));
}

void PrintInt(void *ptr)
{
	printf("%d\n",*((int*)(ptr)));
}

void PrintString(void *ptr)
{
	printf("%s\n",((char*)(ptr)));
}

exit_status_t AddToFloat(void **ptr, int num)
{
	*((float*)*ptr) += num;
	return SUCCESS;
}

exit_status_t AddToInt(void **ptr, int num)
{
	*((int*)*ptr) += num;
	return SUCCESS;
}

exit_status_t AddToString(void **ptr, int num)
{
	char int_formated_to_str[MAX_NUM_DIGITS_IN_INT+1] = {0};
	void *tmp_ptr = NULL;	
	if (0 > sprintf(int_formated_to_str,"%d",num))
	{
		
		return SPRINTF_FAIL;
	}
	tmp_ptr = realloc(*ptr,(strlen((char*)(*ptr)) + strlen(int_formated_to_str) +1)); /*len counts untill 0*/
	if (NULL == tmp_ptr)
	{
		return REALLOC_FAIL;
	}
	*ptr = tmp_ptr;
	strcat(*ptr, int_formated_to_str);
	return SUCCESS;
	
}


void EmptyFunc(void *ptr)
{
	; /* my types dont nead cleanup at this point*/
}

void FreeVarTypesArr(var_types_t *var_types_arr , size_t last_init_indx)
{
	FreeVarHolder(var_types_arr, last_init_indx);
	free(var_types_arr);	
}

void FreeVarHolder(var_types_t *var_types_arr, size_t last_init_indx)
{
	size_t indx = 0;
	for(indx = 0; indx < last_init_indx; ++indx)
	{
		var_types_arr[indx].clean_func(var_types_arr[indx].var_holder);
		free(var_types_arr[indx].var_holder);
	} 	
}

void PrintArrayElements(var_types_t *var_types_arr, size_t size_of_arr)
{

	size_t indx = 0;
	for(indx = 0; indx < size_of_arr; ++indx)
	{
		var_types_arr[indx].print_func(var_types_arr[indx].var_holder);
	} 
	printf("\n");
	
}

exit_status_t AddToEachArrElemnt(var_types_t *var_types_arr, size_t size_of_arr, int num)
{
	
	size_t indx = 0;
	exit_status_t exit_status = SUCCESS;
	
	for(indx = 0; (indx < size_of_arr)&&(SUCCESS == exit_status); ++indx)
	{
		
		var_types_arr[indx].add_func(&(var_types_arr[indx].var_holder), num);
	} 
	if (exit_status != SUCCESS)
	{
		FreeVarTypesArr(var_types_arr , size_of_arr);
		return exit_status;
		
	}
	return SUCCESS;
	
}

exit_status_t TestMax2(void)
{
	if (3 != MAX2(3, 1))
	{
		return ERROR_IN_MAX2;
	}
	if ('c' != MAX2('c', 'a'))
	{
		return ERROR_IN_MAX2;
	}	
	if (3 != MAX2(1, 3))
	{
		return ERROR_IN_MAX2;
	}
	return SUCCESS; 
}

exit_status_t TestMax3(void)
{

	if (3 != MAX3(3, 1, 0))
	{
		return ERROR_IN_MAX3;
	}
	if ('c' != MAX3('c', 'a', 'b'))
	{
		return ERROR_IN_MAX3;
	}	
	if (3.1 != MAX3(1.1, 3.1, 2.1))
	{
		return ERROR_IN_MAX3;
	}
	return SUCCESS;
}

exit_status_t TestSizeOfVar(void)
{
	int test_int = 0;
	char test_char = '\0';
	void *test_ptr = NULL;
	char test_arr[10] = {0};
	
	if ((sizeof (test_int)) != (SIZEOF_VAR(test_int)))
	{
		return ERROR_IN_SIZEOF_VAR;
	}
	if ((sizeof (test_char)) != (SIZEOF_VAR(test_char)))
	{
		return ERROR_IN_SIZEOF_VAR;
	}
	if ((sizeof (test_ptr)) != (SIZEOF_VAR(test_ptr)))
	{
		return ERROR_IN_SIZEOF_VAR;
	}
	if ((sizeof (test_arr)) != (SIZEOF_VAR(test_arr)))
	{
	
		return ERROR_IN_SIZEOF_VAR;
	}

	return SUCCESS;	
}



exit_status_t TestSizeOfType(void)
{
	
	size_t result = 0;
	SIZEOF_TYPE(char, result);
	if ((sizeof (char)) != (result))
	{
		return ERROR_IN_SIZEOF_TYPE;
	}
	SIZEOF_TYPE(int, result);
	if ((sizeof (int)) != (result))
	{
		return ERROR_IN_SIZEOF_TYPE;
	}
	SIZEOF_TYPE(float*, result);
	if ((sizeof (float*)) != (result))
	{
		return ERROR_IN_SIZEOF_TYPE;
	}
	SIZEOF_TYPE(var_types_t, result);
	if ((sizeof (var_types_t)) != result)
	{
	
		return ERROR_IN_SIZEOF_TYPE;
	}

	return SUCCESS;	
}


