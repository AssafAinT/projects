/*****************************************************
 * HASH_TABLE                                        *
 * Assaf Ainhoren                                    *
 * Reviewer: Ahron Cohen                             *
 * date: 17.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcpy */
#include <errno.h> /* perror */
#include <stdlib.h> /* exit */

#include "hash.h"

#define UNUSED(param)  (void)param
#define DICTINARY_MAX_CHAR_IN_WORD 30
#define LINUX_DICTINARY_NUM_Of_WORD 102773


size_t HashFunction(const void *data);
int MatchFunc(const void *hash_data, void *first_name);
int PrintFunc(void *data, void *param);
size_t DicHashFunction(const void *data);
int DicFindWord(const void *hash_data, void *word);
int SpelingChecker(hash_table_ty *dictionary, char *string);

const size_t hash_size = 26;
const size_t dictionary_size = 26 * 2;  


typedef struct student students_ty;

struct student
{
	char first_name[15];
	char last_name[15];
	size_t age;
};

static void CreateHashTableTest(void);
static void HashTableSizeTest(void);
static void HashInsertTest(void);
static void HashFindTest(void);
static void RemoveTest(void);
static void ForEachTest(void);
static void LoadLinuxDictionary(void);
static int IsThisTheRightStudent(students_ty *student1,students_ty *student2);


int main(void)
{

	CreateHashTableTest();
	HashTableSizeTest();
	HashInsertTest();
	HashFindTest();
	RemoveTest();
	ForEachTest();
	LoadLinuxDictionary();
	return (0);
}

static void CreateHashTableTest(void)
{
	size_t desired_size = 20;
	hash_table_ty *new_hash = HashTableCreate(HashFunction,
	                                          MatchFunc,
	                                          desired_size);
	HashTableDestroy(new_hash);
}

static void HashTableSizeTest(void)
{
	size_t desired_size = 3;
	hash_table_ty *new_hash = HashTableCreate(HashFunction,
	                                          MatchFunc,
	                                          desired_size);
	                                          
	assert(0 == HashTableSize(new_hash));
	HashTableDestroy(new_hash);
}

static void HashInsertTest(void)
{
	size_t desired_size = 4;
	hash_table_ty *new_hash = HashTableCreate(HashFunction,
	                                          MatchFunc,
	                                          desired_size);
	students_ty first_student = {0};
	students_ty second_student = {0};
	students_ty third_student = {0};
	students_ty fourth_student = {0};
	
	strcpy(first_student.first_name, "assaf");
	strcpy(first_student.last_name, "ainhoren");
	first_student.age = 28;
	
	strcpy(second_student.first_name, "noa");
	strcpy(second_student.last_name, "dudai");
	second_student.age = 20;
	
	strcpy(third_student.first_name, "ofir");
	strcpy(third_student.last_name, "krisple");
	second_student.age = 22;
	
	strcpy(fourth_student.first_name, "roi");
	strcpy(fourth_student.last_name, "herscho");
	second_student.age = 22;
	assert(1 == HashTableIsEmpty(new_hash));
	HashTableInsert(new_hash, &first_student);
	
	HashTableInsert(new_hash, &second_student);
	HashTableInsert(new_hash, &third_student);
	HashTableInsert(new_hash, &fourth_student);
	assert(4 == HashTableSize(new_hash));
	HashTableDestroy(new_hash);
}

static void HashFindTest(void)
{
	size_t desired_size = 4;
	hash_table_ty *new_hash = HashTableCreate(HashFunction,
	                                          MatchFunc,
	                                          desired_size);
	students_ty first_student = {0};
	students_ty second_student = {0};
	students_ty third_student = {0};
	students_ty fourth_student = {0};

	strcpy(first_student.first_name, "assaf");
	strcpy(first_student.last_name, "ainhoren");
	first_student.age = 28;
	
	strcpy(second_student.first_name, "noa");
	strcpy(second_student.last_name, "dudai");
	second_student.age = 20;
	
	strcpy(third_student.first_name, "ofir");
	strcpy(third_student.last_name, "krisple");
	second_student.age = 22;
	
	strcpy(fourth_student.first_name, "roi");
	strcpy(fourth_student.last_name, "herscho");
	second_student.age = 22;
	assert(1 == HashTableIsEmpty(new_hash));
	HashTableInsert(new_hash, &first_student);
	
	HashTableInsert(new_hash, &second_student);
	HashTableInsert(new_hash, &third_student);
	HashTableInsert(new_hash, &fourth_student);
	assert(4 == HashTableSize(new_hash));
	
	assert(IsThisTheRightStudent(&first_student,
	                             HashTableFind(new_hash,
	                             &first_student)));
	HashTableDestroy(new_hash);
}

static void RemoveTest(void)
{
	size_t desired_size = 4;
	hash_table_ty *new_hash = HashTableCreate(HashFunction,
	                                          MatchFunc,
	                                          desired_size);
	students_ty first_student = {0};
	students_ty second_student = {0};
	students_ty third_student = {0};
	students_ty fourth_student = {0};
	
	strcpy(first_student.first_name, "assaf");
	strcpy(first_student.last_name, "ainhoren");
	first_student.age = 28;
	
	strcpy(second_student.first_name, "noa");
	strcpy(second_student.last_name, "dudai");
	second_student.age = 20;
	
	strcpy(third_student.first_name, "ofir");
	strcpy(third_student.last_name, "krisple");
	second_student.age = 22;
	
	strcpy(fourth_student.first_name, "roi");
	strcpy(fourth_student.last_name, "herscho");
	second_student.age = 22;
	assert(1 == HashTableIsEmpty(new_hash));
	HashTableInsert(new_hash, &first_student);
	
	HashTableInsert(new_hash, &second_student);
	printf("is hash size %ld\n", HashTableSize(new_hash));
	HashTableInsert(new_hash, &third_student);
	printf("is hash size %ld\n", HashTableSize(new_hash));
	HashTableInsert(new_hash, &fourth_student);
	
	HashTableRemove(new_hash, &first_student);
	HashTableRemove(new_hash, &second_student);
	HashTableRemove(new_hash, &third_student);
	HashTableRemove(new_hash, &fourth_student);
	printf("is hash size %ld\n", HashTableSize(new_hash));
	HashTableDestroy(new_hash);
}

static void ForEachTest(void)
{
	size_t desired_size = 4;
	hash_table_ty *new_hash = HashTableCreate(HashFunction,
	                                          MatchFunc,
	                                          desired_size);
	students_ty first_student = {0};
	students_ty second_student = {0};
	
	strcpy(first_student.first_name, "assaf");
	strcpy(first_student.last_name, "ainhoren");
	first_student.age = 28;
	
	strcpy(second_student.first_name, "noa");
	strcpy(second_student.last_name, "dudai");
	second_student.age = 20;
	HashTableInsert(new_hash, &first_student);
	HashTableInsert(new_hash, &second_student);
	HashTableForEach(new_hash, PrintFunc, NULL);
	HashTableDestroy(new_hash);
}
static int IsThisTheRightStudent(students_ty *student1,students_ty *student2)
{
	    return (student1->first_name == student2->first_name &&
            student1->last_name == student2->last_name &&
            student1->age == student2->age);
}
size_t HashFunction(const void *data)
{
	size_t sum = 0;
	students_ty *student = NULL;
	
	student = (students_ty *)data;
	sum = student->age + student->first_name[0];
	
	return(sum % 4);
}

int MatchFunc(const void *hash_data, void *first_name)
{
	
	return (((students_ty *)hash_data)->first_name ==
	       (char *)first_name);
}

int PrintFunc(void *data, void *param)
{
	UNUSED(param);
	
	printf("student name is: %s\n", ((students_ty *)data)->first_name);
	printf("student last_name is: %s\n", ((students_ty *)data)->last_name);
	printf("student age is: %ld\n", ((students_ty *)data)->age);
	
	return (0);
}
void LoadLinuxDictionary(void)
{
	hash_table_ty *dictionary = HashTableCreate(DicHashFunction, 
	                                            DicFindWord,
	                                            dictionary_size);

	char buffers[LINUX_DICTINARY_NUM_Of_WORD][DICTINARY_MAX_CHAR_IN_WORD] = {{0},{0}};
	
	size_t i = 0;
	char *word = "Linux";
	FILE *linux_dict = fopen("/usr/share/dict/british-english", "r");
	
	if (NULL == linux_dict)
	{
		puts("couldn't open file");
		exit(1);
	}
	
	while (fgets(buffers[i], DICTINARY_MAX_CHAR_IN_WORD, linux_dict))
	{
		HashTableInsert(dictionary, &buffers[i]);
		++i;
	}
	
	printf("%s", (char *)HashTableFind(dictionary, word));
	
	if (EOF == fclose(linux_dict))
	{
		puts("error closing the dictionary");
		exit(1);
	}
	assert(0 == SpelingChecker(dictionary, "Linux's"));

	
	HashTableDestroy(dictionary);	
}

size_t DicHashFunction(const void *data)
{	
	return (((char *)data)[0] % hash_size);
}

int DicFindWord(const void *hash_data, void *word)
{
	if (0 != strncmp((char *)hash_data , (char *)word, strlen((char *)hash_data)-1))
	{
		return (0);	
	}
	return (1);
}

int SpelingChecker(hash_table_ty *dictionary, char *string)
{
	char buffer[DICTINARY_MAX_CHAR_IN_WORD] = {0};
	size_t i = 0;
	char *runner = NULL;
	int ret_status = 0;
	assert(NULL != string);
	
	runner = string;
	
	for ( ; ' ' != *runner && '\0' != *runner; ++i, ++runner)
	{
		buffer[i] = *runner;
	}

	if (0 != strncmp(buffer, (char *)HashTableFind(dictionary, buffer),
	                 strlen(buffer)))
	{
		ret_status = 1;
	}
		

	
	return (ret_status);
}

