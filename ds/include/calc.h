/*****************************************************
 * Calculator                                        *
 * Assaf Ainhoren                                    *
 * Reviewer: Maor Fakliro                            *
 * date: 22.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#ifndef __ILRD_OL127_128_CALCULATOR_H__
#define __ILRD_OL127_128_CALCULATOR_H__

/*******************************************************
 * Calculator Description                              *
 * This program emulates a sicentific calculator       *
 * 3 status can be returned from the calculator:       *
 *			SUCCESS - the string evaluated             *
 *			INVALID_EXPRESSION - few examples:         *
 *invalid operators,divide by 0,invalid parentheses,etc*
 * When INVALID_EXPRESSION occures -                   *
 *  the return value is 0.                             *
 *******************************************************/
typedef enum {
    SUCCESS                  = 0, 
    INVALID_EXPRESSION       = 1,
    INSUFFICIENT_MEMORY_FAIL = 2
}status_ty;

/********************************************************
 * Description - Calculate a mathematical expression    *
 *			PARAMS:                                     *
 *              expression - string with expression     *
 *			    *o_status - pointer to status holder    *
 *			RETURN:                                     *
 *			Upon SUCCESS: the evaluated expression      *
 *          Otherwise 0 and o_status filled respectively*
 *******************************************************/
double Calculate(const char *expression, status_ty *o_status);

#endif /* __ILRD_OL127_128_CALCULATOR_H__ */
