#include <iostream>

int main(void)
{
    int a; // no initializer
    int b = 5; // initializer after equals sign
    int c( 6 ); // initializer in parenthesis
    int d { 7 }; // initializer in braces
    int width;
	width = 5; // copy assignment of value 5 into variable width

	// variable width now has value 5

	width = 7; // change value stored in variable width to 7

	// variable width now has value 7

	return 0;
}