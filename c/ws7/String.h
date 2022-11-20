#ifndef STRING_H_ /*include guard */
#define STRING_H_
#include <string.h>           /* for string function compare */ 
#include <strings.h>         /* for strcasecmp func compare */
#include <assert.h>         /* for assert inside functions */
#include <stdlib.h>        /* for malloc in StrDup func   */
#include <ctype.h>        /*       for twolower          */

 /* Copying a string to destination array       		   */
char *StrCpy(char *destination, const char *source); 
/* copying nBytes of the source to destination               */                      
char *StrnCpy(char *destination, const char *source, size_t n_to_copy);
/* comparing two strings                    		  */
int StrCmp( const char *str1, const char *str2);
/* comparing nbytes of two string             		 */
int StrnCmp(const char *str1,  const char *str2, size_t n_cmp);
/* bytes byte comparison between two string ignoring cases */
int StrCaseCmp(const char *str1, const char *str2);
/* returns a pointer to the first occurrence of character  */
char *StrChr(const char *chr_str, int chr_search);
/* returning a pointer to a duplicated new string          */
char *StrDup(const char *to_dup_str);
/* concatenates between two strings                        */
char *StrCat(char *cat_string, char *string_to_cat);
char *StrnCat(char *dest_string, const char *source_str, size_t n_to_cpy);
/* finds the needle in the haystack                        */
char *StrStr(const char *haystack, const char *needle); 
/* returning length of initial segment of a string consists only from the search string */
size_t StrSpn(const char *scanned, const char *search);
/* returns length of a string */ 
size_t StrLen(const char *str);
int Is_Palindrome(const char *string);
#endif /* end guard */
