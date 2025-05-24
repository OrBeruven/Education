/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File for  Test

*****************************/
#include <stdio.h>	/*printf*/
#include <assert.h>	/*assert*/

#include "trie.h"
#include "utilitiestwo.h"

#define SUCCESS 0
#define FAIL 1

#define BITS_IN_BYTE (8)
#define NUM_RESERVED_IP (3)
#define BYTES_IN_IP (4)

/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/
static void TrieTest(void);

/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
static int ConvertIPToInt(char *ip);

/*******************************************************************************

*******************************************************************************/
int main(void)
{
    TrieTest();
    return 0;
}

/*******************************************************************************
                    Test Function Implementation
*******************************************************************************/
static void TrieTest(void)
{
    char ip[4] = {192, 168, 0, 0};
    int ip_i = -1;
    trie_t *trie = TrieCreate(30);

    ip_i = TrieInsert(trie, 1);
    printf("%d\n", ip_i);
    ip_i = TrieInsert(trie, 0);
    printf("%d\n", ip_i);

    ip_i = TrieInsertNext(trie);
    printf("%d\n", ip_i);
    ip_i = TrieInsertNext(trie);
    printf("%d\n", ip_i);
    ip_i = TrieInsertNext(trie);
    printf("%d\n", ip_i);
   
    TrieRemove(trie, 1);
    ip_i = TrieInsert(trie, 1);
    ip_i = TrieInsertNext(trie);
    printf("after remove %d\n", ip_i);

    ip_i = TrieInsert(trie, 3);
    printf("after remove %d\n", ip_i);
    
    TrieDestroy(trie);
}

/*******************************************************************************

*******************************************************************************/
static int ConvertIPToInt(char *ip)
{
    int to_ret = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        for (j = 0; j < BITS_IN_BYTE; ++j)
        {
            to_ret |= ((ip[i] + j) & 1);
            to_ret <<= 1;
        }
    }

    return to_ret;
}

/*static char *ConvertIPToInt(int ip)
{
    int to_ret = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        for (j = 0; j < BITS_IN_BYTE; ++j)
        {
            to_ret |= ((ip + j) & 1);
            to_ret <<= 1;
        }
    }

    return to_ret;
}*/