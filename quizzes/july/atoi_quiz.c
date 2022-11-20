
#include <stdio.h>
#include <assert.h>

#define ZERO_C 48
#define POSITIVE_SIGN 1
#define NEGATIVE_SIGN -1

int Atoi(const char *str);
static int ConvertToDigit(const char ch);

int main(void)
{
	char digits[] = "-234561321";
	char digits1[] = "1010101";
	char digits2[] = "12345671";
	
	printf("%s sent and came back: %d\n", digits, Atoi(digits));
	printf("%s sent and came back: %d\n", digits1, Atoi(digits1));
	printf("%s sent and came back: %d\n", digits2, Atoi(digits2));

	return (0);
}

int Atoi(const char *str)
{
	int sign = POSITIVE_SIGN;
	int result = 0;
	
	assert(NULL != str); 
	if ( '-' == *str)
	{
		sign = NEGATIVE_SIGN;
		++str;
	}
	for ( ; '\0' != *str && ('0' <= *str && '9' >= *str); ++str)
	{
		result = (result * 10) + (ConvertToDigit(*str));
	}
	
	return (sign *result);
}

int ConvertToDigit(const char ch)
{
	return (ch - ZERO_C);
}
