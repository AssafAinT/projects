/*****************************************************
 * State Machine                                     *
 * Assaf Ainhoren                                    *
 * Reviewer: BLANK                                   *
 * date: 17.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

typedef enum
{
	idle_state,
	first_character_one_state,
	first_character_zero_state,
	not_enough_character_state,
	scanning_zero_character_state,
	scanning_one_character_state,
	last_character_one_state,
	last_character_zero_state
}system_state_ty;

system_state_ty BinaryStringStateMachine(char *str);
system_state_ty ScanFirstCharacter(char data);
system_state_ty ScanAndEvaluateTheString(char *str);
system_state_ty ScanStringByOnes(char *str);
system_state_ty IsAtleastTwoCharacters(char *str);

int main(void)
{
	char *string = "011111111110";
	char *string2= "10";
	char *string3= "011";
	char *string4 = "";
	char *string5 = "1";
	char *string6 = "0";
	
	assert(idle_state == BinaryStringStateMachine(string));
	assert(first_character_one_state == BinaryStringStateMachine(string2));
	assert(last_character_one_state == BinaryStringStateMachine(string3));
	assert(not_enough_character_state == BinaryStringStateMachine(string4));
	assert(first_character_one_state == BinaryStringStateMachine(string5));
	assert(not_enough_character_state == BinaryStringStateMachine(string6));
	return (0);
}

system_state_ty BinaryStringStateMachine(char *str)
{
	system_state_ty system_state = idle_state;
	assert(NULL != str);
	
	system_state = ScanFirstCharacter(*str);
	
	if (system_state == first_character_zero_state)
	{
		system_state = IsAtleastTwoCharacters(str);
		
		if (not_enough_character_state != system_state)
		{	
			++str;
			system_state = ScanAndEvaluateTheString(str);
		} 
	}
	
	return(system_state);
}

system_state_ty ScanFirstCharacter(char data)
{
	return (data == '1' ? first_character_one_state:
	        first_character_zero_state );
}

system_state_ty ScanAndEvaluateTheString(char *str)
{
	system_state_ty ret_state = idle_state;
	assert(NULL != str);
	for ( ; '\0' != *str && '0' == *str; ++str)
	{
		/* empty loop */
	}
	if ('\0' == *str)
	{
		return (ret_state);
	}
	
	return (ScanStringByOnes(str));
}

system_state_ty ScanStringByOnes(char *str)
{
	assert(NULL != str);
	for ( ; '\0' != *str && '1' == *str; ++str)
	{
		/* empty loop */
	}
	if ('\0' == *str)
	{
		return (last_character_one_state);
	}
	
	return (ScanAndEvaluateTheString(str));
}
	
system_state_ty IsAtleastTwoCharacters(char *str)
{
	system_state_ty ret = idle_state;
	if ('\0' == *str || '\0' == *(str + 1))
	{
		ret = not_enough_character_state;
	}
	return (ret);
}
