/*
* Assaf Ainhoren
* reviewer:Ofir Krisple 
* WS9 word boundary optimization
*/
#include <stdio.h> /*printf */
#include <string.h> /* for testing with the original mem functions */
#include <stdlib.h> /* malloc */

#include "memoryfuncs.h" /*header file with all self-implemented mem functions */

int main(void)
{
	char string_destination[100]="abcdlolololololololololololo";
	const char source_string[50]="geek for geek and life is amazing thank you all";
	
	char string_destination1[100]="abcdlolololololololololololo";
	const char source_string1[50]="geek for geek and life is amazing thank you all";
	
	
	char set_string[] = "hello how are you doing today?";
	char set_string2[] = "hello how are you doing today?";
	
	/* char move_string[] = "how are the people on planet?";
	char move_source[] = "how are the people on planet?";
	
	char move_string1[] = "how are the people on planet?";
	char move_source1[] = "how are the people on planet?"; */
	
	char test[] = "123456789123456789";
	
	void *p = malloc(10);
	++*(char **)&p;
	printf("is align: %d\n", IsAlign((size_t )p));
	
	MemCpy(p, source_string, 7);
	puts(p);
	
	
	/* calling memset */
	MemSet(set_string, '&',17);
	memset(set_string2, '&', 17);
	puts(set_string);
	puts(set_string2);
	
	/* calling memcpy */
	memcpy(string_destination1, source_string1, 17);
	MemCpy(string_destination, source_string, 17);
	puts(string_destination);
	puts(string_destination1);
	
	MemMove(test +3, test, 9);
	puts(test);

	return (0);
}
