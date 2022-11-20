/*****************************************************
 * Calculator                                        *
 * Assaf Ainhoren                                    *
 * Reviewer: Maor Fakliro                            *
 * date: 22.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /*strtod, strlen */
#include <stdlib.h> /* free */
#include <math.h> /* pow */
#include "calc.h"
#include "stack.h"

#define NUM_OF_STATE 8
#define ASCII_TABLE_SIZE 256
#define UNUSED(param)  (void)param
#define NUM_OF_PRIOR 11

enum priority_table
{
	ADD,
	SUB,
	MULTI,
	DIV,
	POW,
	CLOSED_CIR_BRACKET,
	CLOSED_CUR_BRACKET,
	CLOSED_SQR_BRACKET,
	OPEN_CIR_BRACKET,
	OPEN_CUR_BRACKET,
	OPEN_SQR_BRACKET
		
};
enum flag
{
	FALSE,
	TRUE,
	POP_OPEN_BRACKET = 30
};
typedef enum states
{
	START_STATE, 
 	OPEN_BRACKET, 
	CLOSED_BRACKET,
	OPERATOR_STATE,
	CALCULATE_STATE,
	NUMBER_STATE,
	PRIORITY_STATE,
	SPACE_STATE
}states_ty;

typedef size_t (*transition)(stack_ty *operand_stack,
							    stack_ty *operator_stack,
	                            const char *expression);

static transition transition_table[ASCII_TABLE_SIZE][NUM_OF_STATE] = {{0}, {0}};

static transition priority_table[NUM_OF_PRIOR][NUM_OF_PRIOR] = {{0}, {0}};

static status_ty current_status = SUCCESS;

static void InitializeTransitionLut(void);

static void InitializePriorityLut(void);

static size_t ErrorFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);

static size_t SpaceFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);

static size_t NumFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);

static size_t OperationFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);

static size_t CloseBracketFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);

static size_t OpenBracketFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t ResultFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t AddFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t SubtractFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t DivisionFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t MultiplyFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);        
static size_t PowerFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t OneFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t TwoFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t ThreeFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t FourFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t ZeroFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t EmptyFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t FiveFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t SixFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t SevenFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t EightFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t NineFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t TenFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static size_t PopOpenBracket(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression);
static void PriorityHandler(stack_ty *operand_stack,
                            stack_ty *operator_stack,
							const char *expression);

static status_ty CalculatorCreate(stack_ty **operand_stack,
                                  stack_ty **operator_stack,
								size_t element_amount);

static void CalculatorDestroy(stack_ty *operand_stack,
                            stack_ty *operator_stack);

double CalculateBySubExpression(stack_ty *operand_stack,
	                           stack_ty *operator_stack,
	                           const char *expression,
	                           status_ty *o_status);
	                         
double Calculate(const char *expression, status_ty *o_status)
{
	static int is_inited = FALSE;
	size_t element_amount = strlen(expression);
	double calculated_num = 0.0;
	stack_ty *operand_stack = NULL;
	stack_ty *operator_stack = NULL;
	
	assert(NULL != expression);
	
	*o_status = CalculatorCreate(&operand_stack, &operator_stack,
	                                     element_amount);
	
	if (!is_inited)
	{
		InitializeTransitionLut();
		InitializePriorityLut();
		is_inited = TRUE;		
	}
	
	calculated_num = CalculateBySubExpression(operand_stack,
	                         operator_stack,
	                         expression, o_status);
	CalculatorDestroy(operand_stack, operator_stack);
	return(calculated_num);
}



double CalculateBySubExpression(stack_ty *operand_stack,
	                            stack_ty *operator_stack,
	                            const char *expression,
	                            status_ty *o_status)
{
	current_status = SUCCESS;
	*o_status = transition_table[*(unsigned char*)expression][START_STATE]
								(operand_stack,
	                            operator_stack,
	                            expression);
	                            
	if (!StackIsEmpty(operator_stack) ||
	    1 != StackSize(operand_stack))
	{
		
		*o_status = INVALID_EXPRESSION;
	}
	
	if (INVALID_EXPRESSION == *o_status)
	{
		return (0);
	}                            
	
	return (*(double *)(StackPeek(operand_stack)));
}
                            
static size_t NumFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	double num_to_push = 0;
	assert(NULL != operand_stack);
	assert(NULL != operator_stack);
	assert(NULL != expression);
	
	num_to_push = strtod((const char *)expression, ((char **)&expression));
	StackPush(operand_stack, &num_to_push);
	
	transition_table[*(unsigned char*)expression][NUMBER_STATE]
	                            (operand_stack,
	                            operator_stack,
	                            expression);

	return(current_status);
}

static size_t OperationFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{	
	unsigned char operation_to_push = '\0';


	assert(NULL != operand_stack);
	assert(NULL != operator_stack);
	assert(NULL != expression);
	
	operation_to_push = *expression;
	
	if (!StackIsEmpty(operator_stack))
	{
		PriorityHandler(operand_stack, operator_stack, expression);
	}

	StackPush(operator_stack, &operation_to_push);
	++expression;

		                        
	transition_table[*(unsigned char*)expression][OPERATOR_STATE]
		                        (operand_stack,
		                        operator_stack,
		                        expression);
	
	return (current_status);
}

static void PriorityHandler(stack_ty *operand_stack,
                            stack_ty *operator_stack,
							const char *expression)
{
	unsigned char operator_to_push = '\0';
	unsigned char curr_operator = '\0';
	size_t proirity_curr_operator = 0;
	size_t proirity_operator_to_push = 0;
	
	assert(NULL != operand_stack);
	assert(NULL != operator_stack);
	assert(NULL != expression);
	
	operator_to_push = *expression;
	
	curr_operator = *(unsigned char *)StackPeek(operator_stack); 
	
	proirity_curr_operator = transition_table[curr_operator][PRIORITY_STATE]
														(NULL, NULL, NULL);
														
	proirity_operator_to_push = transition_table[operator_to_push][PRIORITY_STATE]
														(NULL, NULL, NULL);
	
	priority_table[proirity_curr_operator][proirity_operator_to_push](operand_stack,
							   					 					  operator_stack,
							   					 					  NULL);

}

static size_t ResultFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	unsigned char curr_oper = '\0';
	
	while (1 != StackSize(operand_stack) && (!StackIsEmpty(operator_stack)))
	{
		curr_oper = *(char *)StackPeek(operator_stack);
		transition_table[curr_oper][CALCULATE_STATE](operand_stack,
		                                             operator_stack,NULL);
	}
	UNUSED(expression);
	return (current_status);
}

static size_t CloseBracketFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	unsigned char curr_operator = '\0';
	unsigned char next_operator = '\0';
	int status = SUCCESS;
	
	while (!StackIsEmpty(operator_stack) && (status != POP_OPEN_BRACKET))
	{
		curr_operator = *(unsigned char *)StackPeek(operator_stack);
		status = transition_table[curr_operator][CALCULATE_STATE]
								(operand_stack, operator_stack, expression);
	}
	
	++expression;
	next_operator = *expression;
	transition_table[next_operator][CLOSED_BRACKET]
								(operand_stack, operator_stack, expression);
	return (current_status);

}
static size_t OpenBracketFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	unsigned char bracket_to_push = *expression;
	unsigned char current_oper = '\0';
	StackPush(operator_stack, &bracket_to_push);
	++expression;
	current_oper = *expression;
	transition_table[current_oper][OPEN_BRACKET](operand_stack,
		                                             operator_stack,expression);
	return (current_status);
}

static size_t SpaceFunc(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	unsigned char current_oper = '\0';
	++expression;
	current_oper = *expression;
	transition_table[current_oper][SPACE_STATE](operand_stack,
		                                             operator_stack,expression);
	return (current_status);
}
static size_t ErrorFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	current_status = INVALID_EXPRESSION;
	return (current_status);                            
}

static size_t PopOpenBracket(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	unsigned char closed_bracket = *expression;
	unsigned char open_bracket = *(char *)StackPeek(operator_stack);
	
	size_t prior_close_bracket = 0;
	size_t prior_open_bracket = 0;
	UNUSED(operand_stack);
	prior_close_bracket = transition_table[closed_bracket][PRIORITY_STATE]
	                                      (NULL, NULL, NULL);
	prior_open_bracket = transition_table[open_bracket][PRIORITY_STATE]
	                                     (NULL, NULL, NULL);
	current_status = priority_table[prior_open_bracket][prior_close_bracket]
	                               (NULL, NULL, NULL);
	
	if (SUCCESS != current_status)
	{
		StackPop(operator_stack);
		
		return (current_status);	
	}
	StackPop(operator_stack);
	return (POP_OPEN_BRACKET);
}

static size_t AddFunction(stack_ty *operand_stack,
                      stack_ty *operator_stack,
	                  const char *expression)
{
	double first_operand = *(double *)StackPeek(operand_stack);
	double second_operand = 0;
	double result = 0;
	
	UNUSED(expression);
	StackPop(operand_stack);
	
	second_operand = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);
	StackPop(operator_stack);
	result = second_operand + first_operand;
	StackPush(operand_stack, &result);
	return (current_status);
}
static size_t SubtractFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	double first_operand = *(double *)StackPeek(operand_stack);
	double second_operand = 0;
	double result = 0;
	
	UNUSED(expression);
	StackPop(operand_stack);
	
	second_operand = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);
	StackPop(operator_stack);
	result = second_operand - first_operand;
	StackPush(operand_stack, &result);
	return (current_status);
}
static size_t DivisionFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	double first_operand = *(double *)StackPeek(operand_stack);
	double second_operand = 0;
	double result = 0;
	UNUSED(expression);
	
	if (0 == first_operand && StackSize(operand_stack) > 1)
	{
		ErrorFunction(NULL, NULL, NULL);
	}
	StackPop(operand_stack);
	
	second_operand = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);
	StackPop(operator_stack);
	result = second_operand / first_operand;
	StackPush(operand_stack, &result);
	return (current_status);
}
static size_t MultiplyFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	double first_operand = *(double *)StackPeek(operand_stack);
	double second_operand = 0;
	double result = 0;
	
	UNUSED(expression);
	StackPop(operand_stack);
	
	second_operand = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);
	StackPop(operator_stack);
	result = second_operand * first_operand;
	StackPush(operand_stack, &result);
	return (current_status);
}
static size_t PowerFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	double exponent = *(double *)StackPeek(operand_stack);
	double base = 0;
	double result = 0;
	unsigned char next_operator = '\0';
	
	UNUSED(expression);
	StackPop(operand_stack);
	
	base = *(double *)StackPeek(operand_stack);
	StackPop(operand_stack);
	StackPop(operator_stack);
	result = pow(base, exponent);
	StackPush(operand_stack, &result);
	if (!StackIsEmpty(operator_stack))
	{
		next_operator = *(unsigned char *)StackPeek(operator_stack);
		if ('^' == next_operator || '*' == next_operator)
		{
			transition_table[next_operator]
				            [CALCULATE_STATE]
				            (operand_stack, operator_stack, NULL);		
		}
		
	}
	return (current_status);
}
static size_t OneFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (1);
}
static size_t TwoFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (2);
}
static size_t ThreeFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (3);
}
static size_t FourFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (4);
}
static size_t FiveFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (5);
}
static size_t SixFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (6);
}

static size_t SevenFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (7);
}

static size_t EightFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (8);
}
static size_t NineFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (9);
}
static size_t TenFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (10);
}
static size_t ZeroFunction(stack_ty *operand_stack, stack_ty *operator_stack,
	                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	return (0);
}

static void InitializeTransitionLut(void)
{
	size_t i = 0;
	size_t j = 0;
	
	/* Initializing Lut to error func */
	for ( ; i < ASCII_TABLE_SIZE; ++i)
	{
		for(j = 0; j < NUM_OF_STATE; ++j)
		{
			transition_table[i][j] = ErrorFunction;
		}
	}
	/* every space in all states to spacefunc*/
	for (j = 0 ; j < NUM_OF_STATE; ++j)
	{
		transition_table[' '][j] = SpaceFunc;
	}
	for (i = '0' ; i <= '9'; ++i)
	{
		transition_table[i][SPACE_STATE] = NumFunc;
	}
	transition_table['('][SPACE_STATE] = OpenBracketFunc;
	transition_table['['][SPACE_STATE] = OpenBracketFunc;
	transition_table['{'][SPACE_STATE] = OpenBracketFunc;
	transition_table['+'][SPACE_STATE] = OperationFunc;
	transition_table['-'][SPACE_STATE] = OperationFunc;
	transition_table['/'][SPACE_STATE] = OperationFunc;
	transition_table['*'][SPACE_STATE] = OperationFunc;
	transition_table['^'][SPACE_STATE] = OperationFunc;
	transition_table[')'][SPACE_STATE] = CloseBracketFunc;
	transition_table[']'][SPACE_STATE] = CloseBracketFunc;
	transition_table['}'][SPACE_STATE] = CloseBracketFunc;
	
	/* start_state init */
	for (i = '0' ; i <= '9'; ++i)
	{
		transition_table[i][START_STATE] = NumFunc;
	}
	
	transition_table['('][START_STATE] = OpenBracketFunc;
	transition_table['['][START_STATE] = OpenBracketFunc;
	transition_table['{'][START_STATE] = OpenBracketFunc;
	transition_table['+'][START_STATE] = NumFunc;
	transition_table['-'][START_STATE] = NumFunc;
	
	/*operator state init */
	for (i = '0' ; i <= '9'; ++i)
	{
		transition_table[i][OPERATOR_STATE] = NumFunc;
	}
	transition_table['('][OPERATOR_STATE] = OpenBracketFunc;
	transition_table['['][OPERATOR_STATE] = OpenBracketFunc;
	transition_table['{'][OPERATOR_STATE] = OpenBracketFunc;
	transition_table[')'][OPERATOR_STATE] = CloseBracketFunc;
	transition_table[']'][OPERATOR_STATE] = CloseBracketFunc;
	transition_table['}'][OPERATOR_STATE] = CloseBracketFunc;
	transition_table['-'][OPERATOR_STATE] = NumFunc;
	transition_table['+'][OPERATOR_STATE] = NumFunc;
	
	/* open_bracket_state_init */
	for (i = '0' ; i <= '9'; ++i)
	{
		transition_table[i][OPEN_BRACKET] = NumFunc;
	}
	transition_table[')'][OPEN_BRACKET] = OperationFunc;
	transition_table[']'][OPEN_BRACKET] = OperationFunc;
	transition_table['}'][OPEN_BRACKET] = OperationFunc;
	transition_table['('][OPEN_BRACKET] = OpenBracketFunc;
	transition_table['['][OPEN_BRACKET] = OpenBracketFunc;
	transition_table['{'][OPEN_BRACKET] = OpenBracketFunc;

	/* closed bracket state init */
	transition_table[')'][CLOSED_BRACKET] = CloseBracketFunc;
	transition_table[']'][CLOSED_BRACKET] = CloseBracketFunc;
	transition_table['}'][CLOSED_BRACKET] = CloseBracketFunc;
	transition_table['+'][CLOSED_BRACKET] = OperationFunc;
	transition_table['-'][CLOSED_BRACKET] = OperationFunc;
	transition_table['/'][CLOSED_BRACKET] = OperationFunc;
	transition_table['*'][CLOSED_BRACKET] = OperationFunc;
	transition_table['^'][CLOSED_BRACKET] = OperationFunc;

	
	/* initialize number_state init */
	
	transition_table[')'][NUMBER_STATE] = CloseBracketFunc;
	transition_table[']'][NUMBER_STATE] = CloseBracketFunc;
	transition_table['}'][NUMBER_STATE] = CloseBracketFunc;
	transition_table['+'][NUMBER_STATE] = OperationFunc;
	transition_table['-'][NUMBER_STATE] = OperationFunc;
	transition_table['/'][NUMBER_STATE] = OperationFunc;
	transition_table['*'][NUMBER_STATE] = OperationFunc;
	transition_table['^'][NUMBER_STATE] = OperationFunc;
	
	for ( i = 0; i< NUM_OF_STATE; ++i)
	{
		transition_table['\0'][i] = ResultFunction;
	}
	/*calculat state init*/
	transition_table['+'][CALCULATE_STATE] = AddFunction;
	transition_table['-'][CALCULATE_STATE] = SubtractFunction;
	transition_table['*'][CALCULATE_STATE] = MultiplyFunction;
	transition_table['/'][CALCULATE_STATE] = DivisionFunction;
	transition_table['^'][CALCULATE_STATE] = PowerFunction;
	transition_table['('][CALCULATE_STATE] = PopOpenBracket;
	transition_table['['][CALCULATE_STATE] = PopOpenBracket;
	transition_table['{'][CALCULATE_STATE] = PopOpenBracket;

	/*priority_state init*/
	transition_table['+'][PRIORITY_STATE] = ZeroFunction;
	transition_table['-'][PRIORITY_STATE] = OneFunction;
	transition_table['*'][PRIORITY_STATE] = TwoFunction;
	transition_table['/'][PRIORITY_STATE] = ThreeFunction;
	transition_table['^'][PRIORITY_STATE] = FourFunction;
	transition_table[')'][PRIORITY_STATE] = FiveFunction;
	transition_table['}'][PRIORITY_STATE] = SixFunction;
	transition_table[']'][PRIORITY_STATE] = SevenFunction;
	transition_table['('][PRIORITY_STATE] = EightFunction;
	transition_table['{'][PRIORITY_STATE] = NineFunction;
	transition_table['['][PRIORITY_STATE] = TenFunction;

}
static void InitializePriorityLut(void)
{
	const size_t num_of_operators = 5;
	size_t i = 0;
	size_t j =0 ;

	for ( ;i < NUM_OF_PRIOR; ++i)
	{
		for ( j = 0; j < NUM_OF_PRIOR; ++j )
		{
			priority_table[i][j] = EmptyFunction;
		
		}
	}
	
	for (j = 0; j <NUM_OF_PRIOR -3  ; ++j)
	{
		priority_table[j][CLOSED_CIR_BRACKET] = CloseBracketFunc;
		priority_table[j][CLOSED_CUR_BRACKET] = CloseBracketFunc;
		priority_table[j][CLOSED_SQR_BRACKET] = CloseBracketFunc;
	}
	
	for (j = 0; j <num_of_operators  ; ++j)
	{
		priority_table[j][CLOSED_CIR_BRACKET] = ErrorFunction;
		priority_table[j][CLOSED_CUR_BRACKET] = ErrorFunction;
		priority_table[j][CLOSED_SQR_BRACKET] = ErrorFunction;
	}
	priority_table[ADD][ADD] = transition_table['+'][CALCULATE_STATE];
	priority_table[ADD][SUB] = transition_table['+'][CALCULATE_STATE];
	
	priority_table[SUB][SUB] = transition_table['-'][CALCULATE_STATE];
	priority_table[SUB][ADD] = transition_table['-'][CALCULATE_STATE];
	
	priority_table[MULTI][MULTI] = transition_table['*'][CALCULATE_STATE];
    priority_table[MULTI][ADD] = transition_table['*'][CALCULATE_STATE];
    priority_table[MULTI][SUB] = transition_table['*'][CALCULATE_STATE];
    priority_table[MULTI][DIV] = transition_table['*'][CALCULATE_STATE];
    
	
	priority_table[DIV][DIV] = transition_table['/'][CALCULATE_STATE];
	priority_table[DIV][ADD] = transition_table['/'][CALCULATE_STATE];
	priority_table[DIV][SUB] = transition_table['/'][CALCULATE_STATE];
	priority_table[DIV][MULTI] = transition_table['/'][CALCULATE_STATE];
	
    priority_table[OPEN_CIR_BRACKET][CLOSED_CUR_BRACKET] = ErrorFunction;
    priority_table[OPEN_CIR_BRACKET][CLOSED_SQR_BRACKET] = ErrorFunction;
    
    
    priority_table[OPEN_SQR_BRACKET][CLOSED_CUR_BRACKET] = ErrorFunction;
    priority_table[OPEN_SQR_BRACKET][CLOSED_CIR_BRACKET] = ErrorFunction;
    
    priority_table[OPEN_CUR_BRACKET][CLOSED_CIR_BRACKET] = ErrorFunction;
    priority_table[OPEN_CUR_BRACKET][CLOSED_SQR_BRACKET] = ErrorFunction;
    
    priority_table[OPEN_CUR_BRACKET][CLOSED_CIR_BRACKET] = ErrorFunction;
    priority_table[OPEN_CUR_BRACKET][CLOSED_SQR_BRACKET] = ErrorFunction;
    
    priority_table[POW][ADD] = transition_table['^'][CALCULATE_STATE];
    priority_table[POW][SUB] = transition_table['^'][CALCULATE_STATE];
    priority_table[POW][MULTI] = transition_table['^'][CALCULATE_STATE];
    priority_table[POW][DIV] = transition_table['^'][CALCULATE_STATE];

}
static size_t EmptyFunction(stack_ty *operand_stack, stack_ty *operator_stack,
                            const char *expression)
{
	UNUSED(operand_stack);
	UNUSED(operator_stack);
	UNUSED(expression);
	
	return (0);
}
static status_ty CalculatorCreate(stack_ty **operand_stack,
                                  stack_ty **operator_stack,
								size_t element_amount)
{
	status_ty status = SUCCESS;
	*operand_stack = StackCreate(element_amount, sizeof(double));
	if (NULL == operand_stack)
	{
		status = INSUFFICIENT_MEMORY_FAIL;
	}
	*operator_stack = StackCreate(element_amount, sizeof(char));
	
	if (NULL == operand_stack)
	{
		free(operand_stack);
		operand_stack = NULL; 
		status = INSUFFICIENT_MEMORY_FAIL;
	}
	return (status);
}

static void CalculatorDestroy(stack_ty *operand_stack,
                            stack_ty *operator_stack)
{
	StackDestroy(operand_stack);
	operand_stack = NULL;
	StackDestroy(operator_stack);
	operator_stack = NULL;
}
