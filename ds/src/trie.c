/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For  Implemantation

*****************************/
#include <stdlib.h> /*free, malloc*/
#include <math.h>   /*pow*/
#include <assert.h>	/*assert*/

#include "trie.h"

#define SUCCESS 0
#define FAIL 1
#define NUM_OF_BITS_IN_BYTE (8)
#define NUM_OF_BITS_IN_INT (32)

#define FULL 1
#define NOT_FULL 0

typedef struct trienode trienode_t;

typedef enum
{
    OFF = 0,
    ON = 1,
    NUM_OF_BITS = 2
}bits_t;

typedef enum
{
    NOT_FREED = 0,
    FREED = 1,
    DOUBLE_FREE = 2
}free_status_t;

struct trie
{
    trienode_t *root;
    size_t height;
};

struct trienode
{
    trienode_t *children[NUM_OF_BITS];
    int is_full;
};

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
static trienode_t *CreateNode();

static unsigned int TrieInsertRec(trie_t *trie, trienode_t *node, unsigned int key, size_t height, unsigned int mask);

static unsigned int TrieInsertNextRec(trienode_t *node, unsigned int curr_height, unsigned int *path);

static unsigned int TrieRemoveRec(trienode_t *node, unsigned int key, unsigned int height, unsigned int mask);

static void TrieDestroyRec(trienode_t *node);

static size_t TrieCountRec(trienode_t *node);

static void SetIfFull(trienode_t *node);

static unsigned int CreateOffBranch(trienode_t *node, size_t height, unsigned int *path);
/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
trie_t *TrieCreate(unsigned int mask)
{
    trie_t *new_trie = (trie_t *)malloc(sizeof(trie_t));
    if (NULL == new_trie)
    {
        return NULL;
    }

    new_trie->root = CreateNode();
    if (NULL == new_trie->root)
    {
        free(new_trie);
        return NULL;
    }

    new_trie->height = NUM_OF_BITS_IN_INT - mask;

    return new_trie;
}

unsigned int TrieInsert(trie_t *trie, unsigned int key)
{
    unsigned int mask = 0;
    trienode_t *runner = NULL;

    assert(NULL != trie);

    mask = pow(2, trie->height - 1);
    runner = trie->root;
    return TrieInsertRec(trie, runner, key, trie->height, mask);
}

unsigned int TrieInsertNext(trie_t *trie)
{
    unsigned int new_path = 0;

    assert(NULL != trie);

    if (FAIL == TrieInsertNextRec(trie->root, trie->height, &new_path))
    {
        return 0;
    }

    new_path >>= 1;

    return new_path;
}

unsigned int TrieRemove(trie_t *trie, unsigned int key)
{
    unsigned int mask = 0;

    assert(NULL != trie);
    
    mask = pow(2, trie->height - 1);
    
    return TrieRemoveRec(trie->root, key, trie->height, mask);
}

void TrieDestroy(trie_t *trie)
{
    assert(NULL != trie);
    TrieDestroyRec(trie->root);
    free(trie);
}

size_t TrieCount(trie_t *trie)
{
    assert(NULL != trie);
    return TrieCountRec(trie->root);
}

unsigned int TrieSearch(trie_t *trie, unsigned int key)
{
    size_t i = 0;
    trienode_t *runner = NULL;
    unsigned int mask = 0;

    assert(NULL != trie);

    runner = trie->root;
    mask = pow(2, trie->height - 1);

    for (i = 0; i < trie->height; ++i)
    {
        if (NULL == runner->children[!!(key & mask)])
        {
            return FAIL;
        }

        runner = runner->children[!!(key & mask)];
        mask >>= 1;
    }

    return SUCCESS;
}

/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
static trienode_t *CreateNode()
{
    size_t i = 0;
    trienode_t *new_node = (trienode_t *)malloc(sizeof(trienode_t));

    if (NULL == new_node)
    {
        return NULL;
    }

    for (i = 0; i < NUM_OF_BITS; ++i)
    {
        new_node->children[i] = NULL;
    }
    new_node->is_full = NOT_FULL;

    return new_node;
}

static unsigned int TrieInsertRec(trie_t *trie, trienode_t *node, unsigned int key, size_t curr_height, unsigned int mask)
{
    if (node->is_full)
    {
        return FAIL;
    }

    if (0 == curr_height)
    {
        node->is_full = FULL;
        return SUCCESS;
    }

    if (NULL == node->children[!!(key & mask)])
    {
        node->children[!!(key & mask)] = CreateNode();
    }

    if (SUCCESS == TrieInsertRec(trie, node->children[!!(key & mask)], key, curr_height - 1, mask >> 1))
    {
        SetIfFull(node);
        return SUCCESS;
    }

    return FAIL;
}

static unsigned int TrieInsertNextRec(trienode_t *node, unsigned int curr_height, unsigned int *path)
{
    if (FULL == node->is_full)
    {
        return FAIL;
    }

    if (0 == curr_height)
    {
        node->is_full = FULL;
        return SUCCESS;
    }

    if (NULL == node->children[OFF])
    {
        return CreateOffBranch(node, curr_height, path);
    }
    else if (NOT_FULL == node->children[OFF]->is_full)
    {
        *path <<= 1;

        if (SUCCESS == TrieInsertNextRec(node->children[OFF], curr_height - 1, path))
        {
            return SUCCESS;
        }

        *path >>= 1;
    }
    
    if (NULL == node->children[ON])
    {
        node->children[ON] = CreateNode();
        if (NULL == node->children[ON])
        {
            return FAIL;
        }

        *path |= ON;
        *path <<= 1;
        return CreateOffBranch(node->children[ON], curr_height - 1, path);
    }
    else if (NOT_FULL == node->children[ON]->is_full)
    {
        *path |= ON;
        *path <<= 1;

        if (SUCCESS == TrieInsertNextRec(node->children[ON], curr_height - 1, path))
        {
            return SUCCESS;
        }

        *path >>= 1;
    }

    SetIfFull(node);
    return FAIL;
}

static unsigned int TrieRemoveRec(trienode_t *node, unsigned int key, unsigned int height, unsigned int mask)
{
    int has_free = 0;

    if (NULL == node)
    {
        return DOUBLE_FREE;
    }

    if (0 == height)
    {
        free(node);
        return FREED;
    }

    has_free = TrieRemoveRec(node->children[!!(key & mask)], key, height - 1, mask >> 1);

    if (NULL == node->children[ON] && NULL == node->children[OFF])
    {
        free(node);
        return FREED;
    }
    else
    {
        if (FREED == has_free)
        {
            node->children[!!(key & mask)] = NULL;
        }
        node->is_full = NOT_FULL;
        return NOT_FREED;
    }

    return has_free;
}

static void TrieDestroyRec(trienode_t *node)
{
	if (NULL != node)
	{
		TrieDestroyRec(node->children[OFF]);
		TrieDestroyRec(node->children[ON]);
	    free(node);
	}
	
	node = NULL;
}

static size_t TrieCountRec(trienode_t *node)
{
    size_t count = 0;

    if (node == NULL)
    {
        return count;
    }
    if (NULL == node->children[OFF] && NULL == node->children[ON] && node->is_full)
    {
        return count + 1;
    }
    count += TrieCountRec(node->children[OFF]);
    count += TrieCountRec(node->children[ON]);
    return count;
}

static void SetIfFull(trienode_t *node)
{
    if (NULL != node->children[ON] && NULL != node->children[OFF])
    {
        if (FULL == node->children[ON]->is_full && FULL == node->children[OFF]->is_full)
        {
            node->is_full = FULL;
        }
    }
    else
    {
        node->is_full = NOT_FULL;
    }
}

static unsigned int CreateOffBranch(trienode_t *node, size_t height, unsigned int *path)
{
    for (; height > 0; --height)
    {
        *path <<= 1;
        node->children[OFF] = CreateNode();
        if (NULL == node->children[OFF])
        {
            return FAIL;
        }

        node = node->children[OFF];
    }

    node->is_full = FULL;
    return SUCCESS;
}
/*******************************************************************************

*******************************************************************************/
