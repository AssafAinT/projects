/****************************************************
* shuffleSortDict                                   *
* Assaf Ainhoren                                    *
****************************************************/
/********************************libraries includes****************************/
#define _POSIX_C_SOURCE  199309L
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <pthread.h> /* pthread_lib */
#include <omp.h> /* open_mp */
#include <stdlib.h>  /* malloc, free, rand */
#include <sys/stat.h> /* stat */
#include <pthread.h> /* pthread */
#include <string.h> /* memcpy */
#include <time.h> /* time */
#define UNUSED(param)  (void)param
#define DICTINARY_MAX_CHAR_IN_WORD 30
#define LINUX_DICTINARY_NUM_Of_WORD 104334
#define NUM_THREADS 2
#define THREAD_COUNTER 2

static pthread_t threads_arr[NUM_THREADS] = {0};

static size_t num_of_characters = 0;
static size_t g_word_counter = 0;
void CountNumOfChars(char *file_name);
static void ReadDictToBuffer(void);
static void PrintPtrArray(char **buffer);
static void ShufflePtrArray(void *base, size_t nmemb, size_t size);
static int RandCmp(const void *a, const void *b);
static void PrintShufPtrArray(char **buffer);
static void PrintSrtPtrArray(char **buffer);
static void PrintMrgSrtPtrArray(char **buffer);
static void *SortBuff(void *args);
static void MergeSrtPtrArray(void *base, size_t nmemb, size_t size);
static int GoodCmp(const void *a, const void *b);
static void SubTimeSpec(struct timespec t1, struct timespec t2, struct timespec *td);

enum 
{
	NS_PER_SECOND = 1000000000 
};
int main(void)
{
	CountNumOfChars("/usr/share/dict/american-english");
    ReadDictToBuffer();
    return 0;
}

static void ReadDictToBuffer(void)
{
	size_t i = 0;
	char **word_bucket = NULL;
	FILE *linux_dict = NULL;
	char *runner = NULL;
	char **bucket_runner = NULL;
    struct timespec start;
	struct timespec finish;
	struct timespec delta;
	

	char *linux_buffer = (char *)calloc(num_of_characters + 1, sizeof(char));
	if (NULL == linux_buffer)
	{
		return ;
	}
    clock_gettime(CLOCK_REALTIME, &start);
	
	linux_dict = fopen("/usr/share/dict/american-english", "r");
	if (NULL == linux_dict)
	{
		puts("couldn't open file");
		exit(1);
	}
	runner = linux_buffer;
	for (i = 0; i < num_of_characters; ++i, ++runner)
	{
		*runner = fgetc(linux_dict);
		if ('\n' == *runner)
		{
			*runner = '\0';
			++g_word_counter;
		}
	}

	word_bucket = (char **)calloc(THREAD_COUNTER * (g_word_counter), sizeof(char *));
	if (NULL == word_bucket)
	{
		free(linux_buffer);
		linux_buffer = NULL;
	}
	bucket_runner = word_bucket;
	runner = linux_buffer;
	
	*bucket_runner = runner;	
	++bucket_runner;
	for (i = 0 ; i < (num_of_characters - 1) ; ++i , ++runner)
	{
		if ( '\0' == *runner)
		{
			*bucket_runner = runner + 1;
			++bucket_runner;
		}
	}
	
	for (i = 1 ; i < THREAD_COUNTER ; ++i, bucket_runner += g_word_counter)
	{
		printf("you here\n");
		memcpy(bucket_runner, word_bucket, g_word_counter * sizeof(char *));
	}
	PrintPtrArray(word_bucket);
	
	ShufflePtrArray(word_bucket, g_word_counter * THREAD_COUNTER, sizeof(char *));
	PrintShufPtrArray(word_bucket);
	
	bucket_runner = word_bucket;
	for ( i= 0; i < NUM_THREADS ; ++i, bucket_runner += g_word_counter)
    {
        pthread_create(&threads_arr[i], NULL, SortBuff, bucket_runner);
    }
	
	for ( i = 0; i < NUM_THREADS ; ++i)
	{
		pthread_join(threads_arr[i], NULL);
	}	
	PrintSrtPtrArray(word_bucket);

	MergeSrtPtrArray(word_bucket, g_word_counter * THREAD_COUNTER, sizeof(char *));
	PrintMrgSrtPtrArray(word_bucket);

	if (EOF == fclose(linux_dict))
	{
		puts("error closing the dictionary");
		exit(1);
		free(linux_buffer);
		linux_buffer = NULL;
	}

	free(linux_buffer);
	linux_buffer = NULL;
	free(word_bucket);
	word_bucket = NULL;

	clock_gettime(CLOCK_REALTIME, &finish);
    SubTimeSpec(start, finish, &delta);
    printf("TIME IN nano_Second: %d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);

}

void CountNumOfChars(char *file_name)
{
    struct stat file_stat = {0};
    
    if (stat(file_name, &file_stat) == -1)
    {
        perror("stat");
        exit(1);
    }

    num_of_characters = file_stat.st_size;  
	printf("Number is %ld characters\n", num_of_characters);
}

static void PrintPtrArray(char **buffer)
{
	char **start = buffer;
	size_t i = 0;
	FILE *fp = NULL;

	fp = fopen("/home/assaf/git/system_programming/exercise/print.txt", "w");
	if (NULL == fp)
	{
		perror("fopen");
		return ;
	}
	while (i < g_word_counter * THREAD_COUNTER)
	{
		fprintf(fp ,"%s\n", *start);
		++start;
		++i;
	}
	
	if (EOF == fclose(fp))
	{
		perror("fclose");
		return ;
	}

}

static void PrintShufPtrArray(char **buffer)
{
	char **start = buffer;
	size_t i = 0;
	FILE *fp = NULL;
	
	fp = fopen("/home/assaf/git/system_programming/exercise/printshuf.txt", "w");
	if (NULL == fp)
	{
		perror("fopen");
		return ;
	}
	
	while (i < g_word_counter * THREAD_COUNTER)
	{
		fprintf(fp ,"%s\n", *start);
		++start;
		++i;
	}

	if (EOF == fclose(fp))
	{
		perror("fclose");
		return ;
	}
}

static void PrintSrtPtrArray(char **buffer)
{
	char **start = buffer;
	size_t i = 0;
	FILE *fp = NULL;
	fp = fopen("/home/assaf/git/system_programming/exercise/printsrt.txt", "w");
	
	if (NULL == fp)
	{
		perror("fopen");
		return ;
	}

	while (i < g_word_counter * THREAD_COUNTER)
	{
		fprintf(fp ,"%s\n", *start);
		++start;
		++i;
	}

	if (EOF == fclose(fp))
	{
		perror("fclose");
		return ;
	}
}

static void PrintMrgSrtPtrArray(char **buffer)
{
	char **start = buffer;
	size_t i = 0;
	FILE *fp = NULL;
	fp = fopen("/home/assaf/git/system_programming/exercise/printmrgsrt.txt", "w");
	
	if (NULL == fp)
	{
		perror("fopen");
		return ;
	}

	while (i < g_word_counter * THREAD_COUNTER)
	{
		fprintf(fp ,"%s\n", *start);
		++start;
		++i;
	}

	if (EOF == fclose(fp))
	{
		perror("fclose");
		return ;
	}
}
static int RandCmp(const void *a, const void *b)
{
    UNUSED(a);
	UNUSED(b);

    return (rand() % 2 ? +1 : -1);
}

static int GoodCmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
static void ShufflePtrArray(void *base, size_t nmemb, size_t size)
{
    qsort(base, nmemb, size, RandCmp);
}

static void MergeSrtPtrArray(void *base, size_t nmemb, size_t size)
{
	qsort(base, nmemb, size, GoodCmp);
}
static void *SortBuff(void *args)
{
	char **data = args;
	qsort(data, g_word_counter, sizeof(char *), GoodCmp);

	return (NULL);
}

static void SubTimeSpec(struct timespec t1, struct timespec t2, struct timespec *td)
{
	td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }

}