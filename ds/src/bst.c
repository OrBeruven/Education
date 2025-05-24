/*****************************
	Name : Or Beruven

	Reviewed By : Oran

	Date Test: 22.3.2023

	Description : c file for Binary Search Tree

*****************************/

#include <assert.h>	/*assert*/
#include <errno.h>	/*errno, ENOMEM*/
#include <stdlib.h>	/*free, malloc*/
#include <stdio.h>	/*perror*/

#include "bst.h"

#define GET_ROOT(bst) ((bst)->dummy_root.children[LEFT])
#define NO_CHILD NUM_OF_CHILDREN
#define INVALID_ITER(iter) (NULL != (iter))
#define GET_INVALID_ITER NULL

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILDREN];
	void *data;
};

struct binary_search_tree
{
	bst_node_t dummy_root;
	int (*cmp_func)(const void *, const void *);
};

/*************************************************
			Help Function Declerations
**************************************************/
static size_t HeightRec(bst_iter_t iter);

static child_pos_t NumOfChildren(bst_iter_t iter);
static child_pos_t MyParentSide(bst_iter_t iter);


static child_pos_t GetChildSide(bst_iter_t iter);
static bst_iter_t BSTRemoveMidTree(bst_iter_t iter);
/*************************************************
			Function Implemetations
**************************************************/
bst_t *BSTCreate(int (*cmp_func)(const void *, const void *))
{
	bst_t *new = NULL;
	
	assert(NULL != cmp_func);
	
	new = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == new)
	{
		errno = ENOMEM;
		perror("BSTCreate");
		return NULL;
	}
	
	new->dummy_root.children[LEFT] = GET_INVALID_ITER;
	new->dummy_root.children[RIGHT] = GET_INVALID_ITER;
	new->dummy_root.parent = GET_INVALID_ITER;
	new->dummy_root.data = NULL;
	new->cmp_func = cmp_func;
	
	return new;
}

void BSTDestroy(bst_t *bst)
{
	bst_node_t *runner = NULL;
	bst_node_t *runner_parent = NULL;
	size_t tree_size = 0;
	child_pos_t child = NO_CHILD;
	
	assert(NULL != bst);
	
	tree_size = BSTSize(bst);
	runner = GET_ROOT(bst);
	while (0 < tree_size)
	{
		child = GetChildSide(runner);
		if (NO_CHILD == child)
		{
			runner_parent = runner->parent;
			
			runner_parent->children[MyParentSide(runner)] = NULL;
			
			free(runner);
			runner = runner_parent;
			--tree_size;
		}
		
		else if (LEFT == child)
		{
			runner = runner->children[LEFT];
		}
		
		else
		{
			runner = runner->children[RIGHT];
		}
	}
	
	free(bst);
	bst = NULL;
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t runner = GET_INVALID_ITER;
	bst_iter_t runner_parent = GET_INVALID_ITER;
	bst_node_t *new_node = NULL;
	
	assert(NULL != bst);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		errno = ENOMEM;
		perror("BSTInsert");
		return BSTEndIter(bst);
	}
	
	runner_parent = &bst->dummy_root;
	runner = GET_ROOT(bst);
	
	if (!BSTIsEmpty(bst))
	{
		while (INVALID_ITER(runner))
		{
			runner_parent = runner;
			if (0 < bst->cmp_func(data, runner->data))
			{
				runner = runner->children[RIGHT];
				
			}
			else
			{
				runner = runner->children[LEFT];
			}
		}
		
		if (0 < bst->cmp_func(data, runner_parent->data))
		{
			runner_parent->children[RIGHT] = new_node;
		}
		
		else
		{
			runner_parent->children[LEFT] = new_node;
		}
	}
		
	else
	{
		runner_parent->children[LEFT] = new_node;
	}
	
	new_node->parent = runner_parent;
	new_node->data = data;
	new_node->children[LEFT] = GET_INVALID_ITER;
	new_node->children[RIGHT] = GET_INVALID_ITER;
	
	return (bst_iter_t)new_node;	
}

void BSTRemove(bst_iter_t iter)
{
	child_pos_t child = NO_CHILD;
	
	assert(INVALID_ITER(iter));
	
	child = NumOfChildren(iter);
	
	if (NO_CHILD == child)
    {
        iter->parent->children[MyParentSide(iter)] = GET_INVALID_ITER;
    }
    
    else if (LEFT == child)
    {
    	child = GetChildSide(iter);
    	
    	iter->parent->children[MyParentSide(iter)] = iter->children[child];
    	iter->children[child]->parent = iter->parent;
    }
    
    else
    {
    	iter = BSTRemoveMidTree(iter);
 	}
 	   	
	free(iter);
}

bst_iter_t BSTFind(const bst_t *bst, const void *key)
{
	bst_iter_t runner = GET_INVALID_ITER;
	
	assert(NULL != bst);
	assert(NULL != key);
	
	runner = GET_ROOT(bst);
	
	while (INVALID_ITER(runner))
	{
		if (0 == bst->cmp_func(key, runner->data))
		{
			break;
		}
		
		else if (0 < bst->cmp_func(key, runner->data))
		{
			runner = runner->children[RIGHT];
			
		}
		
		else
		{
			runner = runner->children[LEFT];
		}
	}		
	
	return runner;
}

int BSTForEach(bst_iter_t from, const bst_iter_t to, int (*action_func)(void *, void *), void *param)
{
	int result = 0;

	assert(INVALID_ITER(from));
	assert(INVALID_ITER(to));
	assert(NULL != action_func);

	while (!BSTIsSameIter(from, to))
	{
		result = action_func(from->data, param);
		
		if (0 != result)
		{
			return result;
		}
		
		from = BSTNextIter(from);
	}

	return result;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return !INVALID_ITER(bst->dummy_root.children[LEFT]);
}

size_t BSTSize(const bst_t *bst)
{
	size_t size_counter = 0;
	bst_iter_t runner = GET_INVALID_ITER;
	bst_iter_t end = GET_INVALID_ITER;
	
	assert(NULL != bst);
	
	runner = BSTBeginIter(bst);
	end = BSTEndIter(bst);
	
	while (!BSTIsSameIter(runner, end))
	{
		++size_counter;
		runner = BSTNextIter(runner);
	}
	
	return size_counter;
}

void *BSTGetData(bst_iter_t iter)
{
	assert(INVALID_ITER(iter));
	
	return iter->data;
}

size_t BSTHeight(const bst_t *bst)
{
	assert(NULL != bst);
	
	return HeightRec(GET_ROOT(bst));
}
/*************************************************
			Iterators Implemetations
**************************************************/
bst_iter_t BSTBeginIter(const bst_t *bst)
{
	bst_iter_t runner = NULL;
	
	assert(NULL != bst);
	
	runner = (bst_iter_t)&bst->dummy_root;
	
	while (INVALID_ITER(runner->children[LEFT]))
	{
		runner = runner->children[LEFT];
	}
	
	return (bst_iter_t)runner;
}
	
bst_iter_t BSTEndIter(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (bst_iter_t)&bst->dummy_root;
}

bst_iter_t BSTNextIter(const bst_iter_t iter)
{
	bst_iter_t runner = GET_INVALID_ITER;
		
	assert(INVALID_ITER(iter));
		
	runner = iter;
	if (INVALID_ITER(runner->children[RIGHT]))
	{
		runner = runner->children[RIGHT];
		
		while (INVALID_ITER(runner->children[LEFT]))
		{
			runner = runner->children[LEFT];
		}
	}
	
	else
	{	
		while (runner->parent->children[LEFT] != runner)
		{
			runner = runner->parent;
		}
		
		runner = runner->parent;
	}

	return runner;
}

bst_iter_t BSTPrevIter(const bst_iter_t iter)
{
	bst_iter_t runner = GET_INVALID_ITER;
	
	assert(INVALID_ITER(iter));
	
	runner = iter;
	
	if (INVALID_ITER(runner->children[LEFT]))
	{
		runner = runner->children[LEFT];
		
		while (INVALID_ITER(runner->children[RIGHT]))
		{
			runner = runner->children[RIGHT];
		}
	}
	
	else
	{	
		while (runner->parent->children[RIGHT] != runner)
		{
			runner = runner->parent;
		}
		
		runner = runner->parent;
	}

	return runner;
}

int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2)
{
	assert(INVALID_ITER(iter1));
	assert(INVALID_ITER(iter2));
	
	return iter1 == iter2;
}

/*************************************************
		  Help Functions Implemetations
**************************************************/
static size_t HeightRec(bst_iter_t iter)
{
	size_t left_height = 0;
	size_t right_height = 0;

	if (!INVALID_ITER(iter))
	{
		return 0;
	}
	
	if (!INVALID_ITER(iter->children[LEFT]) && !INVALID_ITER(iter->children[RIGHT]))
	{
		return 1;
	}
	
	left_height = HeightRec(iter->children[LEFT]);
	right_height = HeightRec(iter->children[RIGHT]);
	
	return left_height > right_height ? 1 + left_height : 1 + right_height;
}

static bst_iter_t BSTRemoveMidTree(bst_iter_t iter)
{
    bst_iter_t tmp_iter = GET_INVALID_ITER;
    child_pos_t child = NO_CHILD;
    
    assert(INVALID_ITER(iter));
    
    tmp_iter = BSTNextIter(iter);
    iter->data = BSTGetData(tmp_iter);
    
    child = MyParentSide(tmp_iter);
    if (NO_CHILD != NumOfChildren(tmp_iter))
    {
        iter = tmp_iter->parent;
        iter->children[child] = tmp_iter->children[RIGHT];
        tmp_iter->children[RIGHT]->parent = iter;
  		
    }
    
    else
    {
        iter->children[child] = GET_INVALID_ITER;
    }
    
    return tmp_iter;
}

static child_pos_t GetChildSide(bst_iter_t iter)
{
    if (INVALID_ITER(iter->children[LEFT]))
    {
        return LEFT;
    }
    
    if (INVALID_ITER(iter->children[RIGHT]))
    {
        return RIGHT;
    }
    
    return NO_CHILD;
}

static child_pos_t NumOfChildren(bst_iter_t iter)
{
    child_pos_t child = NO_CHILD;
    
    if (INVALID_ITER(iter->children[LEFT]) || INVALID_ITER(iter->children[RIGHT]))
    {
    	if	(INVALID_ITER(iter->children[LEFT]))
    	{
    		child = RIGHT;	/*has 2*/
    	}
    	
    	else
    	{
        	child = LEFT; /*has 1*/
        }
    }
    
    return child; /*has NONE*/
}

static child_pos_t MyParentSide(bst_iter_t iter)
{
    if (iter->parent->children[LEFT] == iter)
    {
        return LEFT;
    }
    
    else
    {
        return RIGHT;
    }
}
/**************************************************/
