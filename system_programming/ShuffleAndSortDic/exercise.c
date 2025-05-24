/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdio.h>  /*fopen, printf*/
#include <stdlib.h> /*exit*/
#include <string.h> /*strlen*/
#include <pthread.h>    /*pthread*/
#include <assert.h>	/*assert*/
#include <aio.h>    /*clock_t*/
#include <time.h>   /*CLOCK_REALTIME*/

#define BILLION  1000000000L;

#define NUM_OF_WORDS 104334
#define NUM_OF_COPIES 4
#define NUM_OF_THREADS 15

#define SUCCESS 0
#define FAILURE 1

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
int RandomSort(const void *a, const void *b);

void *StartRoutine(void *arg);

int CompareSort(const void *a, const void *b);


int MergeSort(char **arr_to_sort, size_t num_elements, int (*comp)(const void *, const void *));

static int MergeSortRec(char **arr, size_t left, size_t right, int (*comp)(const void *, const void *));

static int MergeTwoArr(char **arr, size_t left, size_t mid, size_t right, int (*comp)(const void *, const void *));
/*******************************************************************************

*******************************************************************************/

char *p_dic_words[NUM_OF_WORDS * NUM_OF_COPIES] = {NULL};

/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
int main(void)
{
    char *dictionary_location = "/usr/share/dict/american-english";
    char *buffer = NULL;
    long buffer_size = 0;
    size_t length = 0;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    double accum = 0;

    struct timespec start, stop;
    pthread_t threads[NUM_OF_THREADS];

    FILE *fp = fopen(dictionary_location, "r");

    if (NULL == fp)
    {
        perror("fopen");
        exit(1);
    }

    if (0 != fseek(fp, 0L, SEEK_END)) 
    {
        perror("fseek");
        exit(1);
    }
    
    buffer_size = ftell(fp);
    if (-1 == buffer_size)
    {
        perror("ftell");
        fclose(fp);
        exit(1);    
    }

    buffer = (char *)malloc(sizeof(char) * (buffer_size + 1));
    if (NULL == buffer)
    {
        perror("malloc");
        fclose(fp);
        exit(1);
    }

    if (0 != fseek(fp, 0L, SEEK_SET)) 
    {
        perror("malloc");
        fclose(fp);
        free(buffer);
        exit(1);
    }

    length = fread(buffer, sizeof(char), buffer_size, fp);
    if (0 != ferror(fp)) 
    {
        perror("Error reading file");
        fclose(fp);
        free(buffer);
        exit(1);
    } 
    else 
    {
        buffer[length++] = '\0';
    }

    p_dic_words[0] = &buffer[0];
    p_dic_words[NUM_OF_WORDS] = &buffer[0];
    p_dic_words[2 * NUM_OF_WORDS] = &buffer[0];
    p_dic_words[3 * NUM_OF_WORDS] = &buffer[0]; 
    j = 1;
    for (i = 0; i < (size_t)buffer_size; ++i)
    {
        if ('\n' == buffer[i])
        {
            buffer[i] = '\0';
            for (k = 0; k < NUM_OF_COPIES; ++k)
            {
                p_dic_words[(k * NUM_OF_WORDS) + j] = &buffer[i + 1];
            }
            ++j;
        }
    }

    qsort(p_dic_words, NUM_OF_WORDS * NUM_OF_COPIES, sizeof(char *), RandomSort);

    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, StartRoutine, (void *)i);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    } 

    /* qsort(p_dic_words, NUM_OF_WORDS * NUM_OF_COPIES, sizeof(char *), M); */
    MergeSort(p_dic_words, NUM_OF_WORDS * NUM_OF_COPIES, CompareSort);

    clock_gettime(CLOCK_REALTIME, &stop);
    accum = ( stop.tv_sec - start.tv_sec )
             + (double)( stop.tv_nsec - start.tv_nsec )
               / (double)BILLION;

    printf( "%lf\n", accum );
   /*  for (k = 0; k < 100; ++k)
    {
        printf("%s\n", p_dic_words[k]);
    }
    for (k = 0; k < 100; ++k)
    {
        printf("%s\n", p_dic_words[k + NUM_OF_WORDS]);
    }  */

   
/*
    printf("\n\n");
    for (k = 1; k < 4; ++k)
    {
        printf("%s\n", p_dic_words[0 + k]);
        printf("%s\n", p_dic_words[NUM_OF_WORDS + k]);
        printf("%s\n", p_dic_words[2 * NUM_OF_WORDS + k]);
        printf("%s\n", p_dic_words[3 * NUM_OF_WORDS + k]);
    }
   
    printf("%lu == %lu", length, buffer_size);  */
    fclose(fp);
    free(buffer);
    return 0;
}

/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
int RandomSort(const void *a, const void *b)
{   
    (void)a;
    (void)b;
    return rand()%100 - rand()%100;
}

int CompareSort(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
void *StartRoutine(void *arg)
{
/*    qsort(&p_dic_words[(size_t)arg * NUM_OF_WORDS], NUM_OF_WORDS, sizeof(char *), CompareSort);
 */   
    MergeSort(&p_dic_words[(size_t)arg * ((NUM_OF_WORDS * NUM_OF_COPIES) / NUM_OF_THREADS)], ((NUM_OF_WORDS * NUM_OF_COPIES) / NUM_OF_THREADS), CompareSort);
    return NULL;
}
/*******************************************************************************

*******************************************************************************/

int MergeSort(char **arr_to_sort, size_t num_elements, int (*comp)(const void *, const void *))
{
	return MergeSortRec(arr_to_sort, 0, num_elements - 1, comp);
}

static int MergeSortRec(char **arr, size_t left, size_t right, int (*comp)(const void *, const void *))
{
	int mid = left + ((right - left) / 2);
	
	if (left >= right)
	{
		return SUCCESS;
	}
	
	if (FAILURE == MergeSortRec(arr, left, mid, comp))
	{
		return FAILURE;
	}
	
	if (FAILURE == MergeSortRec(arr, mid + 1, right, comp))
	{
		return FAILURE;
	}
	
	if (FAILURE == MergeTwoArr(arr, left, mid, right, comp))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}


static int MergeTwoArr(char **arr, size_t left, size_t mid, size_t right, int (*comp)(const void *, const void *))
{
	size_t left_length = mid - left + 1;
	size_t right_length = right - mid;
	
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	char **left_arr = NULL;
	char **right_arr = NULL;
	
	left_arr = (char **)malloc(sizeof(char *) * left_length);
	if (NULL == left_arr)
	{
		perror("MergeSort Malloc");
		return FAILURE;
	}
	
	right_arr = (char **)malloc(sizeof(char *) * right_length);
	if (NULL == right_arr)
	{
		perror("MergeSort Malloc");
		return FAILURE;
	}
	
	for (i = 0; i < left_length; ++i)
	{
		left_arr[i] = arr[left + i];
	}
	
	for (i = 0; i < right_length; ++i)
	{
		right_arr[i] = arr[mid + 1 + i];
	}
	
	for (i = 0, j = 0, k = left; k <= right; ++k)
	{
		if (i < left_length)
		{
			if (j >= right_length || 0 > comp(&left_arr[i], &right_arr[j]))
			{
				arr[k] = left_arr[i];
				++i;
			}
			else
			{
				arr[k] = right_arr[j];
				++j;
			}
		}
		else
		{
			arr[k] = right_arr[j];
			++j;
		}
	}
	
	free(left_arr);
	free(right_arr);
	
	return SUCCESS;
}