/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 13.04.2023

	Description : c file for Hash Table implemantation

*****************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include <errno.h>  /*errno, ENOMEM*/
#include <stdio.h>  /*perror*/
#include <math.h>   /*pow, sqrt*/

#include "../include/dll.h"
#include "../include/hash.h"

#define EMPTY 1
#define NOT_EMPTY 0

#define GETLIST(index) (table->hash_table_array[(index)])

typedef enum status
{
    SUCCESS = 0,
    FAILURE = 1
} status_t;

/*******************************************************************************
						Managerial Structure
*******************************************************************************/
struct hash_table
{
    dll_t **hash_table_array;
    size_t capacity;
    size_t(*hash_func)(const void *value);
    int(*is_match_func)(const void *lhd, const void *rhd);
};

/*******************************************************************************
						Help function declarations
*******************************************************************************/
static status_t PushBackToHash(dll_t *dll, void *data);
/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
						API Function Implementation
*******************************************************************************/
hash_table_t *HashTableCreate(size_t capacity, size_t(*hash_func)(const void *value),
                    int(*is_match_func)(const void *lhd, const void *rhd))
{
    hash_table_t *new_table = NULL;
    
    assert(0 < capacity);
    assert(NULL != hash_func);
    assert(NULL != is_match_func);

    new_table = (hash_table_t *)malloc(sizeof(hash_table_t));
    if (NULL == new_table)
    {
        errno = ENOMEM;
        perror("HashTableCreate");
        return NULL;
    }

    new_table->hash_table_array = (dll_t **)calloc(capacity, sizeof(dll_t *));
    if (NULL == new_table->hash_table_array)
    {
        errno = ENOMEM;
        perror("HashTableCreate");
        free(new_table);
        return NULL;
    }

    new_table->capacity = capacity;
    new_table->hash_func = hash_func;
    new_table->is_match_func = is_match_func;

    return new_table;
}            

void HashTableDestroy(hash_table_t *table)
{
    size_t i = 0;

    assert(NULL != table);

    for (i = 0; i < table->capacity; ++i)
    {
        if (NULL != GETLIST(i))
        {
            DLLDestroy(GETLIST(i));
        }
    }

    free(table->hash_table_array);
    free(table);
}

int HashTableInsert(hash_table_t *table, void *data)
{
    size_t new_data_index = 0;

    assert(NULL != table);

    new_data_index = table->hash_func(data) % table->capacity;

    if (NULL == GETLIST(new_data_index))
    {
        GETLIST(new_data_index) = DLLCreate();
        if (NULL == GETLIST(new_data_index))
        {
            return FAILURE;
        }
    }

    return PushBackToHash(GETLIST(new_data_index), data);
}

void HashTableRemove(hash_table_t *table, const void *data)
{
    size_t new_data_index = 0;
    dll_t *dll = NULL;
    iterator_t iter = NULL;

    assert(NULL != table);

    new_data_index = table->hash_func(data) % table->capacity;
    dll = GETLIST(new_data_index);

    if (NULL != dll)
    {
        iter = DLLFind(DLLBeginIter(dll), DLLEndIter(dll), table->is_match_func, (void *)data);
        
        if (!DLLIsSameIter(iter, DLLEndIter(dll)))
        {
            DLLRemove(iter);
        }
    }
}

size_t HashTableSize(const hash_table_t *table)
{
    size_t count = 0;
    size_t i = 0;
    
    assert(NULL != table);

    for (i = 0; i < table->capacity; ++i)
    {
        if (NULL != GETLIST(i))
        {
            count += DLLCount((GETLIST(i)));
        }
    }
    return count;
}

int HashTableIsEmpty(const hash_table_t *table)
{
    size_t i = 0;

    assert(NULL != table);

    for (i = 0; i < table->capacity ; ++i)
    {
        if (NULL != GETLIST(i) && !DLLIsEmpty(GETLIST(i)))
        {
            return NOT_EMPTY;
        }
    }

    return EMPTY;
}

void *HashTableFind(const hash_table_t *table, const void *data)
{
    size_t new_data_index = 0;
    void *to_ret = NULL;
    dll_t *dll = NULL;
    iterator_t iter = NULL;

    assert(NULL != table);

    new_data_index = table->hash_func(data) % table->capacity;
    dll = GETLIST(new_data_index);

    if (NULL != dll)
    {
        iter = DLLFind(DLLBeginIter(dll), DLLEndIter(dll), table->is_match_func, (void *)data);

        if (!DLLIsSameIter(iter, DLLEndIter(dll)))
        {
            to_ret = DLLGetData(iter);
        }
    }

    return to_ret;
}

int HashTableForEach(const hash_table_t *table, 
          int (*action_func)(void *data, void *param), void *param)
{
    size_t i = 0;
    int status = 0;
    
    assert(NULL != table);
    assert(NULL != action_func);

    for (i = 0; i < table->capacity && 0 == status; ++i)
    {
        if (NULL != GETLIST(i))
        {
            status = DLLForEach(DLLBeginIter(GETLIST(i)), DLLEndIter(GETLIST(i)), action_func, param);
        }
    }

    return status;
}

double HashLoad(const hash_table_t *table)
{
    assert(NULL != table);

    return ((double)HashTableSize(table) / (double)table->capacity);
}

double HashSTDev(const hash_table_t *table)
{
    double average = 0;
    double sqd_difference = 0;
    double sum_of_sqd_differences = 0;
    double stdev = 0;
    size_t bucket_size = 0;
    size_t i = 0;

    assert(NULL != table);

    average = HashLoad(table);

    for (i = 0; i < table->capacity; ++i)
    {
        bucket_size = 0;
        if (NULL != table->hash_table_array[i])
        {
            bucket_size = DLLCount(GETLIST(i));
        }

        sqd_difference = pow((double)(bucket_size - average), 2);
        sum_of_sqd_differences += sqd_difference;
    }

    stdev = sum_of_sqd_differences / (table->capacity - 1);

    return (sqrt(stdev));
}

void PrintBuckets(hash_table_t *table, int (*action_func)(void *data, void *param), void *param)
{
    size_t i = 0;

    for (i = 0; i < table->capacity; ++i)
    {
        printf("%lu: ", i);
        if (NULL != GETLIST(i))
        {
            DLLForEach(DLLBeginIter(GETLIST(i)), DLLEndIter(GETLIST(i)), action_func, param);
        }
            printf("\n");
        
    }
}
/*******************************************************************************
*******************************************************************************/
/*******************************************************************************
						Help Function Implementation
*******************************************************************************/
static status_t PushBackToHash(dll_t *dll, void *data)
{
    iterator_t iter = NULL;

    iter = DLLPushBack(dll, data);

    if (DLLIsSameIter(iter, DLLEndIter(dll)))
    {
        return FAILURE;
    }

    return SUCCESS;
}