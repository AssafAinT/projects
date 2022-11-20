/*****************************************************************************************
*	This file was wrtitten and coded by Assaf Ainhoren 			      *
*	In this file you will find a manual copy of string.h library,		      *
*	and in addition check palindrom Function.				      *
******************************************************************************************/

#include <stdio.h>             /* for main and testing        */
#include <string.h>           /* for string function compare */ 
#include <strings.h>         /* for strcasecmp func compare */
#include <assert.h>         /* for assert inside functions */
#include <stdlib.h>        /* for malloc in StrDup func   */
#include <ctype.h>        /*       for twolower          */




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
	const char sub_str[5] = "	";
	
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
	
	
	
char *StrCpy(char *destination, const char *source)             
{
	 /* saving beginning of the string */
	char *head_str = destination;                          
	
	assert( NULL != destination );
	assert( NULL != source );
	
	do 
	{
		*destination = *source;
		++destination;
	}while('\0' != *source++);
	
	return (head_str);
}



char *StrnCpy(char *destination, const char *source, size_t n_to_copy) 
{
	char *head_str = destination;
	
	 /* copying string */
	while((0 < n_to_copy) && ('\0' != *source))                  
	{
		*destination = *source;
		++source;
		++destination;
		--n_to_copy;		
	}
	/* assigning null to remain */
	while(0 < n_to_copy)                                        
	{
		*destination = '\0'; 
		++destination;
		--n_to_copy;
	}
	
	return (head_str);
}
	
	
int StrnCmp(const char *str1,  const char *str2, size_t n_cmp)
{	
	assert( NULL != str1);
	assert( NULL != str2);
	
	while((0 < n_cmp -1) && (*str1 == *str2)&&('\0' != *str1))
	{
		++str1;
		++str2;
		--n_cmp;
	}
		
	return (*str1 - *str2);
}
	
	
int StrCaseCmp(const char *str1, const char *str2)
{

	assert (NULL != str1);
	assert (NULL != str2);
	
	while ( '\0' != *str2 && (tolower(*str1) == tolower(*str2)))
		{
			++str1;
			++str2;
		}

	return (tolower(*str1) - tolower(*str2));		
	
}	

char *StrChr(const char *chr_str, int chr_search)
{
	assert( NULL != chr_str);
	
	do
	{
		if(chr_search == *chr_str)
		{
			return (char *)chr_str;
		}
			
	}while('\0' != *chr_str++);

	return NULL;					                                                 
}

char *StrDup(const char *to_dup_str)
{
	char *dupped_str = NULL ;
	size_t str_size = StrLen(to_dup_str); /* for sizing malloc */                                                                
	
	assert( NULL != to_dup_str);
	dupped_str = (char *)malloc((str_size)*sizeof(char));
	
	if ( NULL != dupped_str)
	{
		return(StrCpy(dupped_str, to_dup_str));
	}
	
	return (NULL);

}


char *StrCat(char *cat_string, char *string_to_cat)
{
	char *head_cat = cat_string;
	
	assert( NULL != cat_string);
	assert( NULL != string_to_cat);
	
	while ('\0' != *cat_string)
	{
		++cat_string;
	}
	
	while('\0' != *string_to_cat)
	{
		*cat_string = *string_to_cat;
		++cat_string;
		++string_to_cat;
	}
	
	*string_to_cat = '\0';
	return (head_cat);
}

char *StrnCat(char *dest_string, const char *source_str,  size_t n_to_cpy)
{
	assert(NULL != dest_string);
	assert(NULL != source_str);
	
	StrnCpy(dest_string + strlen(dest_string), source_str, n_to_cpy);
	
	return(dest_string);
}


char *StrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);
	
	for (; '\0' != *haystack; ++haystack)
	{
		if ((*haystack == *needle) &&
		(StrnCmp(haystack, needle, strlen(needle) - 1) == 0))
		{
			return ((char *) haystack);
		}
	}
	return (NULL); 
}
		
size_t StrSpn(const char *scanned, const char *search)
{
	const char *tmp_search = search;
	size_t length = 0;
	
	assert(NULL != scanned);
	assert(NULL != search);
	
	while ('\0' != *search)
	{
		if( *scanned == *search)
		{
			++length;
			++scanned;
			search = tmp_search;
		}
		else
		{
			++search;
		}
	}
	return length;
}

	
		
int Is_Palindrome(const char *string)
{
	const char *pal_tail = string;
	
	assert(NULL != string);
	
	while('\0' != *pal_tail)
	{
		++pal_tail;
	}
	--pal_tail;
	
	while(string < pal_tail) 
	{
		if (*string != *pal_tail)
		{
			return 1;
		}
		--pal_tail;
		++string;
	}
	return 0;
}
	
			
int StrCmp( const char *str1, const char *str2)
{
	assert (NULL != str1);
	assert (NULL != str2);
	
	while ((*str1 == *str2)&&('\0' != *str1))
	{
		++str1;
		++str2;
	}
	return (*str1 - *str2);
}			
	
size_t StrLen(const char *str)
{
	char *start = (char *)str;
	assert (NULL != str);
	while ('\0' != *str)
	{
		++str;
	}
	return (str - start);
}	
	
