/* WorkSheet 4
* Functions 
* Assaf Ainhoren 
*/
#include <stdio.h>   /* printf */
#include <stdlib.h>  /* system */
#include <stddef.h>  /* size_t */
#define ESC 27       /*defining esc character for exiting*/
#define LUT_SIZE 256 /*defining characters size */

/* defining a pointer function */
typedef void(*LUT)(char key);

/* Printing characters on screen using switch/case control */
void PrintCharacterSwitchCase(); 
/* Printing characters on screen using if/else control */
void PrintCharacterIfElse();
/* using LUT to print   */
void LutGetChar(); 
/* setting empty functions to the function-pointers  */
void EmptyFunction(char c);
/* initializing lut to the desires function or sending to set empty function */
void LutInitializion();
/* print the chosen character */
void PrintChar(char c);
/* assiging the scanned value to the disred place in lut */
void GetCharacterLut(LUT keys_ptr[LUT_SIZE], char key);



int main()
{	

	/* stop terminal buffering and echoing */
	system("stty -icanon -echo");
	
	LutInitializion();               
	/*now the implement is switch/case */
	printf("LUT control finished\nnow same idea onswitch/case - press ESC to quit this control\n");
	PrintCharacterSwitchCase();
	/*now the implement is if/else*/
	printf("switch/case finished\nnow same idea on if/else - press ESC to finish the program.\n");
	PrintCharacterIfElse();
	/* returning the terminal to function normally */
	system("stty icanon echo"); 
		
	return (0);
}

void LutInitializion()
{
	size_t i=0;
	
	/* declaring function array pointer */
	LUT keys_ptr[LUT_SIZE]; 
	
	for ( i = 0 ; i < LUT_SIZE; ++i)
		{
			keys_ptr[i] = EmptyFunction;
		}		
		keys_ptr['a'] = &PrintChar;     
		keys_ptr['A'] = &PrintChar; 
		keys_ptr['t'] = &PrintChar; 
		keys_ptr['T'] = &PrintChar; 
		
		GetCharacterLut(keys_ptr, getchar());	
}

void EmptyFunction(char c)
{
	(void)c;
}

void GetCharacterLut(LUT keys_ptr[LUT_SIZE], char key)
{	
 
	while( ESC != key)
	{
		(*keys_ptr[(unsigned char)key])(key);
		key = getchar();
		
	}
}

void PrintChar(char c)
{
	printf("%c pressed\n", c);
}

void PrintCharacterSwitchCase()
{
	char button_pressed = 0;
	
	while(1)
	{
		button_pressed = getchar();
		switch (button_pressed)
		{
			case 'A':
			case 'a':
				printf("%c is pressed\n", button_pressed);
				break;
			case 'T':
			case 't':
				printf("%c is pressed\n", button_pressed);
				break;
			case ESC:
				printf("you pressed Esc project terminated\ngoodbye!\n");
				return;
		}
	}
}

void PrintCharacterIfElse()
{
	char button_pressed = 0;
	
	while(1)
	{
		button_pressed = getchar();
		if( 'A' == button_pressed || 'a' == button_pressed)
		{
			printf("%c is pressed\n", button_pressed);
		}
		else if( 't' == button_pressed || 't' == button_pressed)
		{
			printf("%c is pressed\n", button_pressed);
		}
		else if ( ESC == button_pressed )
		{
			printf("you pressed Esc project terminated\ngoodbye!\n");
			break;
		}
	}	
}	

			
