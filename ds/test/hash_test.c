/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 13.04.2023

	Description : c file for Hash Table Test

*****************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strcmp*/
#include <assert.h> /*assert*/

#include "../include/hash.h"
#include "../include/utilitiestwo.h"

#define LONGEST_WORD (40)
#define DICT_CAP (104334)

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void InsertRemoveSizeTest(void);

static void IsEmptyTest(void);

static void FindTest(void);

static void ForEachTest(void);

static void LoadTest(void);

static void StandardDeviationTest(void);

static void DictionaryTest(void);
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
						Help function declarations
*******************************************************************************/
static int IsMatch(const void *lhs, const void *rhs);

static size_t HashFunc(const void *value);

static int ActionFunc(void *data, void *param);

static size_t DictionaryHashFunc(const void *value);

static int IsMatchDict(const void *lhd, const void *rhd);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	HEADER(Create. Destroy and Size Test);
    CreateDestroyTest();
    printf("\n");

    HEADER(Insert And Remove Test);
    InsertRemoveSizeTest();
    printf("\n");

    HEADER(Is Empty Test);
    IsEmptyTest();
    printf("\n");

    HEADER(Find Test);
    FindTest();
    printf("\n");

    HEADER(For Each Test);
    ForEachTest();
    printf("\n");

    HEADER(Load Test);
    LoadTest();
    printf("\n");

    HEADER(Standard Deviation Test);
    StandardDeviationTest();
    printf("\n");
    
    HEADER(Standard Deviation Test);
    DictionaryTest();
    printf("\n");
    
    return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/
static void CreateDestroyTest(void)
{	
	hash_table_t *table = NULL;
	
	RESULT_STATUS(table == NULL, 1, BeforeCreation);
	
	table = HashTableCreate(2, HashFunc, IsMatch);
	RESULT_STATUS(table == NULL, 0, Creation);

	HashTableDestroy(table);
}

static void InsertRemoveSizeTest(void)
{
    hash_table_t *table = NULL;
	char *str1 = "1";
    char *str2 = "02";
    char *str3 = "03";
    char *str4 = "Number 4";
    char *str5 = "this is number 5";

	table = HashTableCreate(4, HashFunc, IsMatch);
    RESULT_STATUS(HashTableInsert(table, &str1), 0, Inserted);
	RESULT_STATUS(HashTableSize(table), 1, );

    RESULT_STATUS(HashTableInsert(table, &str2), 0, Inserted);
	RESULT_STATUS(HashTableSize(table), 2, );

    HashTableRemove(table, &str2);
	RESULT_STATUS(HashTableSize(table), 1, Removed);

    HashTableInsert(table, &str2);
    HashTableInsert(table, &str3);
    HashTableInsert(table, &str4);
    HashTableInsert(table, &str5);
    RESULT_STATUS(HashTableSize(table), 5, Size);

    HashTableRemove(table, &str2);
    RESULT_STATUS(HashTableSize(table), 4, );
    HashTableRemove(table, &str4);
    RESULT_STATUS(HashTableSize(table), 3, );

	HashTableDestroy(table);
}

static void IsEmptyTest(void)
{
    hash_table_t *table = NULL;
	char *str1 = "1";
    char *str2 = "02";

    table = HashTableCreate(4, HashFunc, IsMatch);
    RESULT_STATUS(HashTableIsEmpty(table), 1, Is Empty);
    HashTableInsert(table, &str1);
    RESULT_STATUS(HashTableIsEmpty(table), 0, Isnt Empty);
	HashTableInsert(table, &str2);
    RESULT_STATUS(HashTableIsEmpty(table), 0, Isnt Empty);
    HashTableRemove(table, &str2);
    RESULT_STATUS(HashTableIsEmpty(table), 0, Isnt Empty);
    HashTableRemove(table, &str1);
    RESULT_STATUS(HashTableIsEmpty(table), 1, Is Empty);

    HashTableDestroy(table);
}

static void FindTest(void)
{
    hash_table_t *table = NULL;
    void **found = NULL;
	char *str1 = "1";
    char *str2 = "02";
    char *str3 = "03";
    char *str4 = "Number 4";
    char *str5 = "this is number 5";
    char *str6 = "Not here";

	table = HashTableCreate(4, HashFunc, IsMatch);
    HashTableInsert(table, &str1);
	found = HashTableFind(table, &str1);
    RESULT_STATUS(IsMatch(*found, str1), 1, Find);

    HashTableInsert(table, &str2);
    HashTableInsert(table, &str3);
    HashTableInsert(table, &str4);
    HashTableInsert(table, &str5); 

    found = HashTableFind(table, &str3);
    RESULT_STATUS(IsMatch(*found, str3), 1, );
    found = HashTableFind(table, &str2);
    RESULT_STATUS(IsMatch(*found, str3), 0, );
    found = HashTableFind(table, &str5);
    RESULT_STATUS(IsMatch(*found, str5), 1, );
    found = HashTableFind(table, &str4);
    RESULT_STATUS(IsMatch(*found, str4), 1, );
    found = HashTableFind(table, &str6);
    RESULT_STATUS(NULL == found, 1, Not Find);

	HashTableDestroy(table);
}

static void ForEachTest(void)
{
    hash_table_t *table = NULL;
	char *str1 = "1";
    char *str2 = "03";
    char *str3 = "3";
    char *str4 = "02";
    char *str5 = "01";

	table = HashTableCreate(4, HashFunc, IsMatch);
    HashTableInsert(table, &str1);
    HashTableInsert(table, &str2);
    HashTableInsert(table, &str3);
    HashTableInsert(table, &str4);
    HashTableInsert(table, &str5); 

    HashTableForEach(table, ActionFunc, NULL);
    /*should be : 
    1
    3
    03
    02
    01
    */

    HashTableDestroy(table);
}

static void LoadTest(void)
{
    hash_table_t *table = NULL;
	char *str1 = "1";
    char *str2 = "03";
    char *str3 = "3";
    char *str4 = "02";
    char *str5 = "01";

	table = HashTableCreate(4, HashFunc, IsMatch);

    RESULT_STATUS(HashLoad(table), 0, NONE);

    HashTableInsert(table, &str1);
    RESULT_STATUS(HashLoad(table), (double)1 / (double)4, 1 / 4);

    HashTableInsert(table, &str2);
    RESULT_STATUS(HashLoad(table), (double)2 / (double)4, 2 / 4);

    HashTableInsert(table, &str3);
    RESULT_STATUS(HashLoad(table), (double)3 / (double)4, 3 / 4);

    HashTableInsert(table, &str4);
    RESULT_STATUS(HashLoad(table), (double)4 / (double)4, 4 / 4);

    HashTableInsert(table, &str5); 
    RESULT_STATUS(HashLoad(table), (double)5 / (double)4, 5 / 4);

    HashTableDestroy(table);
}

static void StandardDeviationTest(void)
{
    hash_table_t *table = NULL;
	char *str1 = "1";
    char *str2 = "03";
    char *str3 = "3";
    char *str4 = "02";

	table = HashTableCreate(4, HashFunc, IsMatch);
    HashTableInsert(table, &str1);
    HashTableInsert(table, &str2);
    HashTableInsert(table, &str3);
    HashTableInsert(table, &str4);

    printf("%f\n", HashSTDev(table));
    RESULT_STATUS((float)HashSTDev(table), (float)1.154701, Deviation);
    HashTableDestroy(table);
}

static void DictionaryTest(void)
{
    hash_table_t *hash_table = NULL;
    char dictionary[DICT_CAP][LONGEST_WORD] = {{0}};
    char *fp_name = "/usr/share/dict/words";
    FILE *fp = NULL;
    size_t word_len = 0;
    char word_to_search[LONGEST_WORD] = {0};
    char *word_to_search_ptr = NULL;
    size_t i = 0;

    hash_table = HashTableCreate(DICT_CAP, DictionaryHashFunc, IsMatchDict);
    fp = fopen(fp_name, "r");

    if (NULL == fp) 
    {
        printf("Error opening fp!\n");
    }

    for ( i = 0; i < 104334 ; ++i)
    {
        fgets((dictionary[i]), LONGEST_WORD, fp);
        word_len = strlen(dictionary[i]);

        if (word_len > 0 && '\n' == dictionary[i][word_len - 1])
        {
            dictionary[i][word_len - 1] = '\0';
        }

        HashTableInsert(hash_table , dictionary + i);
    }

    
   printf("the number of words is %lu\n",HashTableSize(hash_table));

    printf("Enter a word to be searched in the dictionary:\n");
    scanf(" %s", word_to_search);
    
    word_to_search_ptr = word_to_search;

    printf("SpellChecker :\n");
    RESULT_STATUS((NULL != (HashTableFind(hash_table, word_to_search_ptr))) , 1, Positive);
    

    fclose(fp);
    HashTableDestroy(hash_table);
}









static int IsMatch(const void *lhs, const void *rhs)
{
    return strcmp((const char *)lhs, (const char *)rhs) == 0;
}

static size_t HashFunc(const void *value)
{
    assert (NULL != value);

    return strlen(*(char **)value);
}

static int ActionFunc(void *data, void *param)
{
    (void)param;
    printf("%s, ", *(char**)data);
    return 0;
}

static int IsMatchDict(const void *lhd, const void *rhd)
{
	return strcmp((char *)lhd, (char *)rhd) == 0;
}

static size_t DictionaryHashFunc(const void *value)
{
    size_t hash_value = 31;
    int ch = 0;
    char *str = NULL;

    assert (NULL != value);
    
    str = (char *)value;
    ch = *str;
    while ('\0' != ch)
    {
        hash_value = ((hash_value << 5) + hash_value) + ch;
        ++(str);
        ch = *str;
    }

    return hash_value;
}