/****************************************************
* MultiThreadCountingSort                           *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <pthread.h> /* pthread_lib */
#include <omp.h> /* open_mp */
#include <stdlib.h> 
#include <sys/stat.h> /* stat */
#include <pthread.h> /* pthread */

#define ASCII_TABLE_SIZE 256
#define UNUSED(param)  (void)param
#define DICTINARY_MAX_CHAR_IN_WORD 30
#define LINUX_DICTINARY_NUM_Of_WORD 102773
#define NUM_THREADS 8

static pthread_t threads_arr[NUM_THREADS] = {0};
size_t char_appearence[ASCII_TABLE_SIZE][NUM_THREADS] = {{0}};
size_t char_appearence_sum[ASCII_TABLE_SIZE] = {0};
static size_t num_of_characters = 0;


void *CountApper(void *params);
void CountNumOfChars(char *file_name);
static int ThreadCreate(char *file_name);
static void SumAndPrintHistogramma(void);
typedef struct thread
{
    char *file_name;
    size_t i;
    size_t bytes_to_read;
    size_t off_set;
}thread_params;

int main(int argc, char *argv[])
{
    /*printf("the maximum number of threads is %d\n",  omp_get_max_threads());*/
    printf("file name is %s\n", argv[1]);
    ThreadCreate(argv[1]);

    return (0);
}

static int ThreadCreate(char *file_name)
{
    thread_params thread_params[NUM_THREADS];
    size_t i = 0;
    
    size_t bytes_to_skip = 0;
    

    CountNumOfChars(file_name);

    for ( ; i < (NUM_THREADS - 1); ++i)
    {
        bytes_to_skip = bytes_to_skip + num_of_characters / NUM_THREADS;
        thread_params[i].file_name = file_name;
        thread_params[i].i = i;
        thread_params[i].bytes_to_read = num_of_characters / NUM_THREADS;
        thread_params[i].off_set = num_of_characters / NUM_THREADS * i;
        pthread_create(&threads_arr[i], NULL, CountApper, &thread_params[i]);
    }
    
    thread_params[i].file_name = file_name;
    thread_params[i].i = i;
    thread_params[i].bytes_to_read = num_of_characters / NUM_THREADS +
    num_of_characters % NUM_THREADS;
    thread_params[i].off_set = num_of_characters / NUM_THREADS * i;
    pthread_create(&threads_arr[i], NULL, CountApper, &thread_params[i]);
    

    for(i = 0;i < NUM_THREADS; ++i)
    {
        pthread_join(threads_arr[i], NULL);
    }
    
    SumAndPrintHistogramma();
    return 0;



    /*printf("the num of characters in the file is %d\n", num_of_characters);*/

	/*FILE *linux_dict = fopen("/usr/share/dict/british-english", "r");	
	if (NULL == linux_dict)
	{
		puts("couldn't open file");
		exit(1);
	}*/

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
}

void *CountApper(void *params)
{
    unsigned char ch = '\0';
    thread_params *th_param = NULL;
    FILE *file_to_send = NULL;

    th_param = (thread_params *)params;
    
    file_to_send = fopen(th_param->file_name, "r");
    if (NULL == file_to_send)
    {
        puts("Error: Could not open file");
        return NULL;
    }

    fseek(file_to_send, th_param->off_set, SEEK_SET);
    while (0 != th_param->bytes_to_read)
    {
        ch = fgetc(file_to_send);
        printf("%c read\n", ch);
        ++(char_appearence[ch][th_param->i]);

        --th_param->bytes_to_read;
    }
    fclose(file_to_send);
    return (NULL);   
}
/*
void CountApper(const char *file_name, size_t char_lut[ASCII_TABLE_SIZE])
{
    unsigned char ch = '\0';
    FILE *linux_dict = fopen(file_name, "r");
    if (NULL == linux_dict)
	{
		puts("couldn't open file");
		exit(1);
	}
    while (!feof(file))
	{
		ch = fgetc(file);
        ++char_lut[ch];
        printf("%ld in char_lut[%c]\n", char_lut[ch], ch);
	}
    fclose(linux_dict);
}
*/
static void SumAndPrintHistogramma(void)
{
    size_t i =0;
    size_t k =0;
    for(i = 0;i < ASCII_TABLE_SIZE ;++i)
    {
        for(k = 0;k < NUM_THREADS; ++k)
        {
            char_appearence_sum[i] += char_appearence[i][k];
        }

        if ( 0 != char_appearence_sum[i] )
        {
            if(i < 32)
            {
                printf("%ld occurrences of 0x%x\n", char_appearence_sum[i] , i);
            }
            else if (i < 128)
            {
                printf("%li occurrences of %c\n",char_appearence_sum[i] , i);
            }
            else
            {
                printf("%li occurrences of 0x%x\n", char_appearence_sum[i] , i);
            }
        }
    
    }

}