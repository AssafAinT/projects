/*****************************************************************************************
*	This file was wrtitten and coded by Assaf Ainhoren 			      *
*	In this file you will find a manual copy of string.h library,		      *
*	and in addition check palindrom Function.				      *
******************************************************************************************/

#include <stdio.h>             /* for main and testing        */
#include "String.h"

/* main function to run tests */
int main ()   
{
	/*  for StrnCpy   */
	size_t size_to_cpy = 4; 
	/*  for StrnCmp   */                          
	size_t to_cmp = 4;                                
	
	/*  for StrCmp    */
	const char comp_array1[15] = "GeeksLife";       
	const char comp_array2[15] = "1 2 3 %&*\n"; 
	   
	/* for StrCaseCmp */   
	const char case_array1[20] = "assa123434af";   
	const char case_array2[20] = "ASSss67687AF"; 
	
	/*  for StrnCmp   */
	const char ncmp_array1[20] = "abc";          
	const char ncmp_array2[20] = "kbc"; 
	
	 /*  for StrCpy    */ 
	const char array_to_cop[20] = "assa123434af";                                         
	char dest_array[20];
	                                                           
	/*  for StrnCpy    */ 
	const char array_ncop[20] = "ass54263a123434af";                             
	char dest_ncop[20];
					                          
	/* for StrChr        */
	const char chr_str[10] = "dog";                                           
	char search = '\0';  
	                                                   					    
	 /* for StrCat/nCat    */
	char concat_string[40] = "I love C and its ";			  
	char to_concat[10] = "FUN!!";					   
	
	/* for StrStr      */
	const char haystack[10] = "abcd";
	const char needle[3] = "cd";
	
	/* for StrSpn      */
	const char full_string[20] = "abxxcd245621";
	const char sub_str[5] = "ab	";
	
	/* for StrDup         */
	char *source = "I love c blalalala";				    
	char *target = StrDup(source);
	
	/* FOR IS PALINDROME */
	const char is_pal[10] = "\n\t\n";
	
	                                     
	/* Testing outputs starts from here */
	
	if(0 == Is_Palindrome(is_pal))
	{
		printf("Is palindrome!\n\n");
	}
	else
	{
		printf("Not palindrome!\n\n");
	}
	
	
	printf("After calling StrDup source string is %s and the duplicated is %s\n\n", source, target);
	free(target);
	
	printf("the haystack is the length of %ld\n\n", StrLen(haystack));
	printf("StrCat returned: %s\n\n", StrCat(concat_string, to_concat));
	printf("After that StrnCat returned: %s\n\n", StrnCat(concat_string, to_concat, 2));
	printf("StrStr found substring: %s\n\n", StrStr(haystack, needle));
	printf("the length of the substring is %ld\n\n", StrSpn(full_string, sub_str));
	printf("the length of the substring is %ld\n\n", strspn(full_string, sub_str)); 
	

	
	if(StrCpy(dest_array, array_to_cop) == strcpy(dest_array, array_to_cop))
	{
		printf("StrCpy successed\n\n");
	}
	else 
	{
		printf("StrCpy failed\n\n");
	} 
	
	if(StrnCmp(ncmp_array1, ncmp_array2, to_cmp) == strncmp(ncmp_array1, ncmp_array2, to_cmp))
	{
		printf("StrnCmp successed\n\n");
	}
	else 
	{
		printf("StrnCmp failed\n\n");
	}
	if(StrCmp(comp_array1, comp_array2) == strcmp(comp_array1, comp_array2))
	{
		printf("StrCmp successed\n\n");
	}
	else 
	{
		printf("StrCmp failed\n\n");
	}
	if(StrnCpy(dest_ncop, array_ncop, size_to_cpy) == strncpy(dest_ncop, array_ncop, size_to_cpy))
	{
		printf("StrnCpy successed\n\n");
	}
	else 
	{
		printf("StrnCpy failed\n\n");
	} 
	
	if(StrCaseCmp(case_array1, case_array2) == strcasecmp(case_array1, case_array2))
	{
		printf("StrCaseCmp successed\n\n");
	}
	else 
	{
		printf("StrCaseCmp failed\n\n");
	}
	if(StrChr(chr_str, search) == strchr(chr_str, search))
	{
		printf("StrChr successed\n\n");
	}
	else 
	{
		printf("StrChr failed\n\n");
	}
	
	return (0);
}		
	
	
	

	
	




	
		

	
