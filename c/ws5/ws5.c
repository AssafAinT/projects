/* WS5
* Assaf Ainhoren
* 19/05/2022 */

/* File logger product has the following features:
* at the beginning of the every-line you will have to click any button in-order to procced
* if you wish to stop the program all you have to do is click x between lines
* untop of that this product has to option to: remove the current file(remove), count no * of lines (-count), add to the beginning of the file (<string) and exit(-exit) the      * program  
*/ 

 
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */
#include <errno.h> /* errno */
#include <assert.h> /* assert */

/* creating macros to avoid Magic numbers */
#define FILE_NAME_SIZE 20 
#define MAX_STRING_SIZE 80
#define SIZE_OF_STRUCT_ARRAY 10
#define SIZE_OF_FILE_STRUCT 5
#define EXIT 'x'
#define UNUSED(param)  (void)param

typedef enum flag {SUCCESS,NEED_TO_EXIT,REMOVED_SUCCSESS, FAIL, FAILED_TO_REMOVE, OPEN_FILE_FAILED, FAIL_TO_EXIT,FAILED_TO_ADD_BEGIN, FAILED_TO_APPEND}status_t;

/* printing the int the struct holds */
void PrintNumInStuct();
/* Initialize the int iside each element of struct */
void InitializeNumInStruct();
/* Assigning the relevant function to each struct element */
void AssignFuncToStruct();
/* Writing strings to a file */
status_t WriteToFile(const char *file_name); 
/* initializing Filemanager */
void InitializeFileManager();
/* remove the files from the directory */
status_t RemoveFile(char *string, const char *file_name);
/* put the current string in the beginning */
status_t ToBeggining(char *string, const char *file_name);
/* exit the program */
status_t Exit(char *string, const char *file_name);
/* counting the number of lines */
status_t Count(char *string, const char *file_name);
/* compares special cases to string from user */
status_t StrCmp(const char *str1, const char *str2);
/* Choosing the right feature  */
status_t RunFileHandler(char *string_to_check,const char *file_name);
/* File logger primary function */
void FileLogger(const char *file_name);
/* Function for appending strings */
status_t AppendTheString(char *string, const char *file_name);
/* For approving the add of string */ 
status_t FileHandled(const char *string, const char *file_name);

/* typedef for function pointers */
typedef status_t(*compare)(const char *str1, const char *str2);
typedef status_t(*operation)(char *string, const char *file_name);

/* struct for exercise 1 */
static struct print_me
{
	int num_to_print;
	void (*int_to_send)(int num);
}print_obj[SIZE_OF_STRUCT_ARRAY]; 

/* struct for exercise 2*/
static struct file_operation
{
	char *string;
	compare cmp;
	operation op;
}file_handler[SIZE_OF_FILE_STRUCT];


int main(int argc, char *argv[])
{
	UNUSED(argc);
	
	FileLogger(argv[1]);
	
	InitializeNumInStruct();
	 
	return (SUCCESS);
}

void FileLogger(const char *file_name)
{
	InitializeFileManager();
	 WriteToFile(file_name);
	
}	
void InitializeFileManager()
{
	enum task_of_file{exit, count, remove, to_beginning, append};
	size_t i = 0; 
	
	for ( ;i < SIZE_OF_FILE_STRUCT; ++i)
	{
		file_handler[i].cmp = StrCmp;
	}
	file_handler[exit].op = Exit;
	file_handler[exit].string = "-exit";
	file_handler[count].op = Count;
	file_handler[count].string = "-count";
	file_handler[remove].op = RemoveFile;
	file_handler[remove].string = "-remove";
	file_handler[to_beginning].op = ToBeggining;
	file_handler[to_beginning].string = "<";
	file_handler[append].op = AppendTheString;
	file_handler[append].string = "";
	file_handler[append].cmp = FileHandled;
	
}


status_t WriteToFile(const char *file_name)
{
	char string_to_append[MAX_STRING_SIZE];
	char is_continue = 0;
	FILE *fp = NULL;

	status_t what_is_status = 0;
	
	assert(NULL != file_name);
	
	system("stty -icanon -echo");
	is_continue = getchar();
	while(EXIT != is_continue)
	{
		fp = fopen(file_name, "a+");
		if (NULL == fp)
		{
		return(OPEN_FILE_FAILED);
		}
		
		system("stty icanon echo");
		fgets(string_to_append, MAX_STRING_SIZE, stdin);
		what_is_status = RunFileHandler(string_to_append,file_name);
		if (SUCCESS != what_is_status)
		{
			fclose(fp);
			return(what_is_status);
		}
		system("stty -icanon -echo");
		is_continue = getchar();
		fclose(fp);
	}
	system("stty icanon echo");
	return(SUCCESS);
}
		
status_t RunFileHandler(char *string_to_check, const char *file_name)
{		
		
		size_t i = 0;
		status_t status = 0;
		
		assert(NULL != file_name); 
		for ( ; i< 5; ++i)
		{
			if(file_handler[i].cmp(file_handler[i].string, string_to_check) == 0)
			{
				status = file_handler[i].op(string_to_check, file_name);
				switch (status)
				{
					case SUCCESS:
					return (SUCCESS);
					
					case FAIL:
					return (FAIL);
					
					case FAIL_TO_EXIT:
					return (FAIL_TO_EXIT);
					
					case FAILED_TO_ADD_BEGIN:
					return (FAILED_TO_ADD_BEGIN);
					
					case FAILED_TO_APPEND:
					return (FAILED_TO_APPEND);
					
					case OPEN_FILE_FAILED:
					return (OPEN_FILE_FAILED);
					
					case FAILED_TO_REMOVE:
					return (FAILED_TO_REMOVE);
					
					case REMOVED_SUCCSESS:
					return (REMOVED_SUCCSESS);
					
					case NEED_TO_EXIT:
					return(NEED_TO_EXIT);
					
				}
			}
		}
		return (FAIL);
}

status_t StrCmp(const char *str1, const char *str2)
{
	assert (NULL != str1);
	assert (NULL != str2);
	
	while (('\0' != *str1)&&(*str1 == *str2))
	{
		++str1;
		++str2;
	}
	if ('\0' == *str1)     /* going backwards from null-character */
	{
		--str1;
		--str2;
	}	
	return (*str1 - *str2);
}

status_t RemoveFile(char *string, const char *file_name)
{	
	UNUSED(string);
	
	assert(NULL != file_name);
	
	if(remove(file_name) == 0)
	{
		return(REMOVED_SUCCSESS); 
		
	}
	return (FAILED_TO_REMOVE);
	
}

status_t Exit(char *string, const char *file_name)
{
	
	FILE *fp = NULL;
	UNUSED(string);
	assert(NULL != file_name);
	
	fp = fopen(file_name, "a+");
	if (NULL == fp)
	{
		return(OPEN_FILE_FAILED);
	}
	
	if(fclose(fp)==0)
	{
		return(NEED_TO_EXIT);
	}
	return(FAIL_TO_EXIT);
}

	
status_t Count(char *string, const char *file_name)
{
	
	char ch = '\0';
	int lines = 0 ;
	FILE *fp = NULL;
	UNUSED(string);
	
	assert(NULL != file_name);
	
	fp = fopen(file_name, "r");
	if (NULL == fp)
	{
		return(FAIL);
	}	
	
	while (!feof(fp))
	{
		if ('\n' == ch)
		{
			++lines;
		}
		ch = fgetc(fp);
		
	}
	fclose(fp);

	printf("%d number of lines\n", lines);
	return (lines);
}


status_t ToBeggining(char *string_to_append, const char *file_name)
{
	FILE *file_source = fopen(file_name, "r");
	FILE *file_copy = fopen("file_copy", "a");
	char ch = '\0';
	
	if (NULL == file_source)
	{
		perror("file not available\n");
		return(OPEN_FILE_FAILED);
	}
	if (NULL == file_copy)
	{
		perror("file not available\n");
		return(OPEN_FILE_FAILED);
	}	
	/*add new line to beginning of copy new file*/
	printf("Enter your string :\n");
	if(EOF == fputs(++string_to_append ,file_copy))
	{
		return(FAILED_TO_ADD_BEGIN);
	}

	/*copy the rest of the source file to the copy*/
	ch = fgetc(file_source);
	while(!feof(file_source))
	{
		fputc(ch, file_copy);
		ch = fgetc(file_source);
	}

	/* clean source file and isert all the copy file */
	fclose(file_source);
	fclose(file_copy);
	
	file_source = fopen(file_name, "w");
	file_copy = fopen("file_copy", "r");
	
	ch = fgetc(file_copy);
	while(!feof(file_copy))
	{
		fputc(ch, file_source);
		ch = fgetc(file_copy);
	}
	/* closing files before returning to handler */
	fclose(file_source);
	fclose(file_copy);
	
	remove("file_copy");
	return(SUCCESS);
}

status_t AppendTheString(char *string, const char *file_name)
{
	FILE *fp = NULL;
	assert(NULL != file_name);
	
	fp = fopen(file_name, "a+");
	if (NULL == fp)
	{
		return(OPEN_FILE_FAILED);
	}
	fputs(string, fp);
	return(FileHandled(string, file_name));
}
		
status_t FileHandled(const char *string, const char *file_name)
{
	UNUSED(string);
	UNUSED(file_name);
	
	return (SUCCESS);
}

/******************* beginning of Exercise 1 ********************/
			
void InitializeNumInStruct() 
{
	size_t i = 0;
	for( ; i<SIZE_OF_STRUCT_ARRAY;i++)
	{
		print_obj[i].num_to_print = i;	 
	}
	AssignFuncToStruct();
	
} 

void AssignFuncToStruct()
{
	size_t i = 0;
	for( ; i<SIZE_OF_STRUCT_ARRAY; i++)
	{
		print_obj[i].int_to_send = PrintNumInStuct;
		print_obj[i].int_to_send(print_obj[i].num_to_print); /* sending the nums to PrintNumInStruct */	 
	}
	
}

void PrintNumInStuct(int num)
{
	printf("%d\n", num);
}


