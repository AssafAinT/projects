#include <stdio.h>
#include <stddef.h> /*for size of function */

void DataPrint();

int main()
{
	DataPrint();
	
	return (0);
}

void DataPrint()
{
	printf("The size of 'short int' type is: %ld\n", sizeof(short int));
        printf("The size of 'unsigned short int' type is: %ld\n", sizeof(unsigned short int));
        printf("The size of 'unsigned int' type is: %ld\n", sizeof(unsigned int));
        printf("The size of 'int' type is: %ld\n", sizeof(int));
        printf("The size of 'long int' type is: %ld\n", sizeof(long int));
        printf("The size of 'unsigned long int' type is: %ld\n", sizeof(unsigned long int));
        printf("The size of 'signed char' type is: %ld\n", sizeof(signed char));
        printf("The size of 'unsigned char' type is: %ld\n", sizeof(unsigned char));
        printf("The size of 'float' type is: %ld\n", sizeof(float));
        printf("The size of 'double' type is: %ld\n", sizeof(double));
        printf("The size of 'long double' type is: %ld\n", sizeof(long double));
}
