/*****************************************************
 * C Exam                                            *
 * Assaf Ainhoren                                    *
 * Reviewer: Maayan                                  *
 * date: 16.06.21                                    *
 *****************************************************/
#include <stdio.h> /* printf, size_t */
#include <limits.h> /* CHAR_BIT */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

int FlipDigitsInNum(int num);
unsigned char ByteMirror(unsigned char c);
int FlipBit(int val, unsigned int n);
unsigned char CountSetBits(unsigned char c);
void Pswap(int **p1, int **p2);
char RotateLeft(char byte, unsigned int nbits);
size_t StrLen(const char *string);
char *StrCpy(char *dest, const char *src);
unsigned long int GetFibonacciElement(unsigned int n);
char *IntToString(int num, char *dest, size_t dest_len);
static size_t CountDigits(int num);
unsigned int MultiBy8(unsigned int num);
int main(void)
{
	struct s
	{
		int *i;
		char c;
		short s;
		int *j;
	};
	
	struct s2 
	{
		unsigned int i:2;
		unsigned char c:1;
		unsigned short s:3;
		int *j;
		unsigned char x:2;
	};
	
	union
  {
      char array[7];
      int i;
      short s;
  } jack;


	int p1 = 7;
	int p2 = 12;
	char stringed[]="boomboomchakala";
	char to_copy[] = "";
	
	char *s1 = "hello";
	char s2[] = "hello";
	char *s3 = s1;
	
	
	printf("%d\n",FlipDigitsInNum(-520));
	printf("%d\n", ByteMirror(1));
	printf("%d\n", FlipBit(30, 5));
	assert(2 == CountSetBits(12));
	Pswap(&p1, &p2);
	assert(StrLen(stringed)==strlen(stringed));
	printf("%d\n", RotateLeft(40,1));
	printf("%s\n", StrCpy(to_copy, stringed));
	printf("%lu\n", GetFibonacciElement(20));
	printf("%s\n", IntToString(1233,to_copy, 4));
	assert(24 == MultiBy8(3));
	assert(0 == MultiBy8(0));
	
	/***************** exercise 16 ************/
	printf("%lu %lu %lu %lu \n",sizeof(s1),sizeof(s2), strlen(s1), strlen(s2));
	
	/*s3[0] = 'H';
	printf("%s\n", s3); read-only and tried to access */
	
	
	/***************** exercise 21/22************/
	assert (24 == sizeof(struct s));
	assert (24 == sizeof(struct s2));
	
	/***************** exercise 21/22************/
	assert (8 == sizeof(jack));
	
	return (0);
}
/*----------------------------------------------------------------------------*/
/*                               1.FlipDigitsInNum                            */
/*----------------------------------------------------------------------------*/

int FlipDigitsInNum(int num)
{
	int res = 0;
	int remainder = 0;
	
	if (0 == num)
	{
		return (num);
	}
	
	for ( ; 0 != num; num/=10)
	{
		remainder = num %10;
		res = (res * 10) + remainder;
	}
	return (res);
}
/*----------------------------------------------------------------------------*/
/*                               2.Bin to Hexadecimal                         */
/*----------------------------------------------------------------------------*/

/* the num in binary : 11001110100110011101100011110111
* the num in Hex: 0xCE99D8F7 */

/*----------------------------------------------------------------------------*/
/*                               3.variable Values                            */
/*----------------------------------------------------------------------------*/

/* auto/local : garbage values.
 * static/global : 0 */
 
/*----------------------------------------------------------------------------*/
/*                               4.ByteMirror                                 */
/*----------------------------------------------------------------------------*/
unsigned char ByteMirror(unsigned char c) 
{

    c = (((c & 0xaa) >> 1) | ((c & 0x55) << 1));
    c = (((c & 0xcc) >> 2) | ((c & 0x33) << 2));
    c = (((c & 0xf0) >> 4) | ((c & 0x0f) << 4));

    return(c);
}
/*----------------------------------------------------------------------------*/
/*                               5.FlipBit                                    */
/*----------------------------------------------------------------------------*/
int FlipBit(int val, unsigned int n)
{
	unsigned int mask = 1;
	assert (n <= 31);
	
	mask <<= (n-1);
	
	return(val ^= (mask));
}
/*----------------------------------------------------------------------------*/
/*                               6.CountSetBits                               */
/*----------------------------------------------------------------------------*/
unsigned char CountSetBits(unsigned char c)
{
	size_t  set_bits = 0;
	unsigned char mask = 1;
	
	while(c)
	{
		set_bits += (c & mask);      
		c >>= mask;
	}
	return set_bits;
}
/*----------------------------------------------------------------------------*/
/*                               7.Size_t Usage                               */
/*----------------------------------------------------------------------------*/

/* the usage of size_t is an unsigned int for type that typically used for holding a size of an 
objects in bytes, indexes, and a counter(non negavtive number). furthermore
size_t is portabilly to differents machines. */


/*----------------------------------------------------------------------------*/
/*                               8.RotateLeft                                 */
/*----------------------------------------------------------------------------*/
char RotateLeft(char byte, unsigned int nbits)
{
	return((byte << nbits)|
			byte >> (CHAR_BIT-nbits));
}

/*----------------------------------------------------------------------------*/
/*                 9.Numbers appear different                                 */
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/*                 10.pointers Swap                                           */
/*----------------------------------------------------------------------------*/

void Pswap(int **p1, int **p2)
{
	assert(NULL != p1);
	assert(NULL != p2);
	
	if (p1 != p2)
	{
		*p1 = *p1 + *p2;
		*p2 = *p1 - *p2;
		*p1 = *p1 - *p2;
	}
}
/*----------------------------------------------------------------------------*/
/*                 11.StrLen                                                  */
/*----------------------------------------------------------------------------*/

size_t StrLen(const char *string)
{
	const char *start = NULL;
	assert(NULL != string);
	
	start = string;
	while ('\0' != *string)
	{
		++string;
	}
	return (string - start);
}
/*----------------------------------------------------------------------------*/
/*                 11.StrCmp                                                  */
/*----------------------------------------------------------------------------*/
int StrCmp(const char *string1, const char *string2)
{
	assert(NULL != string1);
	assert(NULL != string2);
	
	while ((*string1 == *string2) && ('\0' != *string1))
	{
		++string1;
		++string2;
	}
	
	return (*string1-*string2);
}
/*----------------------------------------------------------------------------*/
/*                 11.StrCpy                                                  */
/*----------------------------------------------------------------------------*/
char *StrCpy(char *dest, const char *src)
{
	char *dest_to_send = NULL;
	assert(NULL != dest);
	assert(NULL != src);
	
	dest_to_send = dest;
	
	do
	{
		*dest = *src;
		++dest;
	}while('\0' != *src++);
	
	return(dest_to_send);
}
/*----------------------------------------------------------------------------*/
/*                 11.StrnCpy                                                  */
/*----------------------------------------------------------------------------*/
char *StrnCpy(char *dest, const char *src, size_t n)
{
	char *dest_to_send = NULL;
	assert(NULL != dest);
	assert(NULL != src);

	dest_to_send = dest;
	
	while( (0 < n) && ('\0' != *src))
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	while (0 < n)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return (dest_to_send);
}

/*----------------------------------------------------------------------------*/
/*                 11.StrnCpy                                                  */
/*----------------------------------------------------------------------------*/
char *StrCat(char *dest, const char *src)
{
	char *cpy_of_dest = NULL;
	assert(NULL != dest);
	assert(NULL != src);
	
	cpy_of_dest = dest + StrLen(dest);
	
	StrCpy(cpy_of_dest, src);
	
	return (dest);
}
/*----------------------------------------------------------------------------*/
/*                 12.GetFibonacciElement                                      */
/*----------------------------------------------------------------------------*/

unsigned long int GetFibonacciElement(unsigned int n)
{
	unsigned int index = 3;
	unsigned int fib1 = 0;
	unsigned int fib2 = 1;
	unsigned long int fib_n = fib1 + fib2;
	
	if (0 == n)
	{
		return 0;
	}
	
	for ( ; index <=n; ++index)
	{
		fib1 = fib2;
		fib2 = fib_n;
		fib_n = fib1 +fib2;
	}
	return (fib_n);
}

/*----------------------------------------------------------------------------*/
/*                 13.IntToString                                             */
/*----------------------------------------------------------------------------*/

char *IntToString(int num, char *dest, size_t dest_len)
{
	assert(NULL != dest);
	
	if (CountDigits(num) > dest_len)
	{
		return NULL;
	}
	if (0 > sprintf(dest, "%d", num))
	{
		return NULL;
	}
	
	return dest;
}

static size_t CountDigits(int num)
{
	size_t count = 0;
	while(num)
	{
		++count;
		num /= 10;
	}
	return count;
}
/*----------------------------------------------------------------------------*/
/*                 14.MultiBy8                                             */
/*----------------------------------------------------------------------------*/

unsigned int MultiBy8(unsigned int num)
{
	return ( num <<= 3);
}

