/****************************************************
* sqrt                                              *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <math.h> /* sqrt */

double Sqrt(double number);
int main(void)
{
    double number = 16;
    double number2 = 33;
    double number3 = 38;
    double number4 = 12.2;
    double number5 = 0.25;
    
    assert(sqrt(number) == Sqrt(number));
    assert(sqrt(number2) == Sqrt(number2));
    
    printf("the Sqrt of %f is %f\n", number3, Sqrt(number3));
    printf("the sqrt of %f is %f\n", number3, sqrt(number3));

    printf("the Sqrt of %f is %f\n", number4, Sqrt(number4));
    printf("the sqrt of %f is %f\n", number4, sqrt(number4));

    printf("the Sqrt of %f is %f\n", number5, Sqrt(number5));
    printf("the sqrt of %f is %f\n", number5, sqrt(number5));

    return (0);
}
double Sqrt(double number)
{
    double result = 0;
    double num_holders = 0;


    result = number / 2 ;

    while (num_holders != result)
    {
        num_holders = result;

        result = (number / num_holders + num_holders) /2;
    }

    return (result);
}
