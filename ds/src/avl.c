/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 26.03.2023

	Description : c file for AVL Tree Implemetation

*****************************/

#include <assert.h>	/*assert*/
#include <errno.h>	/*errno, ENOMEM*/
#include <stdlib.h>	/*free, malloc*/
#include <stdio.h>	/*perror*/

#include "avl.h"

#define GET_ROOT(bst) ((bst)->dummy_root.children[LEFT])
#define NO_CHILD NUM_OF_CHILDREN
#define IS_FULL_PARENT(node) (NULL != (node)->children[LEFT] && NULL != (node)->children[RIGHT])

#define MAX_2(x, y) ((x) > (y) ? (x) : (y))

#define SUCCESS 0
#define FAILURE 1

typedef struct avl_node avl_node_t;

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct avl_node
{
    avl_node_t *children[NUM_OF_CHILDREN];
    void *data;
    size_t height;
};

struct avl_tree
{
	avl_node_t dummy_root;
	int (*cmp_func)(const void *, const void *);
};

/*************************************************
			Help Function Declerations
**************************************************/
static void DestroyRec(avl_node_t *node);
static size_t InsertRec(avl_t *avl, avl_node_t *node, avl_node_t *new_node, void *data);
static void RemoveRec(avl_t *avl, avl_node_t *root, const void *key);
static avl_node_t *FindRec(const avl_t *avl, avl_node_t *node, const void *key);
static size_t CountRec(avl_node_t *node);

/***************For Each Funtions******************/
static int ForEachInOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param);
static int ForEachPostOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param);
static int ForEachPreOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param);

/****************Node Operations********************/
static avl_node_t *CreateLeaf(avl_node_t *node, void *data, size_t height);
static int IsLeaf(avl_node_t *node);
static child_pos_t GetChildSide(avl_node_t *node);
static avl_node_t *FindLowest(avl_node_t *root);
static size_t GetNodeHeight(avl_node_t *node);

/***************AVL Operations**********************/
static void Rebalance(avl_node_t *node, int balance);
static int GetNodeBalance(avl_node_t *node);
static void UpdateNodeHeight(avl_node_t *node);
static void LeftRotate(avl_node_t *node);
static void RightRotate(avl_node_t *node);
static avl_node_t *ToRemove(avl_t *avl, avl_node_t *root, avl_node_t *to_remove, child_pos_t side);
/*************************************************
			Function Implemetations
**************************************************/
avl_t *AVLCreate(int (*cmp_func)(const void *, const void *))
{
	avl_t *new = NULL;
	
	assert(NULL != cmp_func);
	
	new = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == new)
	{
		errno = ENOMEM;
		perror("BSTCreate");
		return NULL;
	}

	new->cmp_func = cmp_func;
	
	CreateLeaf(&new->dummy_root, NULL, 0);
	
	return new;
}

void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	DestroyRec(GET_ROOT(avl));
	free(avl);
}

int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *new_node = NULL;
	
	assert(NULL != avl);
	assert(NULL != data);
	
	new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if (NULL == new_node)
	{
		errno = ENOMEM;
		perror("AVLInsert");
		return FAILURE;
	}
	
	if (NULL == GET_ROOT(avl))
	{
		CreateLeaf(new_node, data, 1);
		GET_ROOT(avl) = new_node;
	}
	else
	{
		InsertRec(avl, GET_ROOT(avl), new_node, data);
	}
	
	return SUCCESS;
}

void AVLRemove(avl_t *avl, const void *key)
{
	assert(NULL != avl);
	assert(NULL != key);
	
	if (IsLeaf(GET_ROOT(avl)))
	{
		free(GET_ROOT(avl));
		GET_ROOT(avl) = NULL;
		return;
	}

	RemoveRec(avl, GET_ROOT(avl), key);
}
	
	
void *AVLFind(const avl_t *avl, const void *key)
{
	avl_node_t *temp = NULL;
	assert(NULL != avl);
	assert(NULL != key);
	
	temp = FindRec(avl, GET_ROOT(avl), key);
	return NULL == temp ? NULL : temp->data;
}

int AVLForEach(avl_t *avl, int (*action_func)(void *, void *), void *param, order_t order)
{
	assert(NULL != avl);
	assert(NULL != action_func);
	
	switch (order)
	{
		case IN_ORDER:
			return ForEachInOrder(GET_ROOT(avl), action_func, param);
			
		case POST_ORDER:
			return ForEachPostOrder(GET_ROOT(avl), action_func, param);
		
		case PRE_ORDER:
			return ForEachPreOrder(GET_ROOT(avl), action_func, param);
	}
	
	return FAILURE;
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == GET_ROOT(avl));
}

size_t AVLCount(const avl_t *avl)
{
	assert(NULL != avl);
	
	return CountRec(GET_ROOT(avl));
}
	
size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);
	
	return GetNodeHeight(GET_ROOT(avl));
}	
	
/*************************************************
		  Help Functions Implemetations
**************************************************/
static void DestroyRec(avl_node_t *node)
{
	if (NULL != node)
	{
		DestroyRec(node->children[LEFT]);
		DestroyRec(node->children[RIGHT]);
	}
	
	free(node);
	node = NULL;
}

static size_t InsertRec(avl_t *avl, avl_node_t *node, avl_node_t *new_node, void *data)
{	
	size_t growth_factor = 0;
	child_pos_t side = LEFT;
	
	if (0 > avl->cmp_func(node->data, data))
	{
		side = RIGHT;
	}
	
	if (NULL == node->children[side])
	{	
		node->children[side] = CreateLeaf(new_node, data, 1);
		
		if (node->height <= node->children[side]->height)
		{
			node->height = node->children[side]->height + 1;
			return 1;
		}
		
		return 0;
	}
	else
	{
		growth_factor = InsertRec(avl, node->children[side], new_node, data);
		
		if (growth_factor)
		{
			Rebalance(node, GetNodeBalance(node));
		}
		
		UpdateNodeHeight(node);
		
		return growth_factor;
	}
	
}

static void RemoveRec(avl_t *avl, avl_node_t *root, const void *key)
{
	avl_node_t *to_remove = NULL;
	child_pos_t side = LEFT;
	
	if (NULL == root)
	{
		return;
	}
	
	if (0 > avl->cmp_func(root->data, key))
	{
		side = RIGHT;
	}
	
	if (0 == avl->cmp_func(root->data, key))
	{
		to_remove = root;
		
		root = ToRemove(avl, root, to_remove, side);
	}	
	else if (NULL != root->children[side] && 0 == avl->cmp_func(root->children[side]->data, key))
	{
		to_remove = root->children[side];
		
		ToRemove(avl, root, to_remove, side);
	}
	else
	{
		RemoveRec(avl, root->children[side], key);
	}
	
	/*Balancing, using side as temp*/
	side = GetNodeBalance(root);
	if (1 < side || -1 > (int)side)
	{
		Rebalance(root, side);
	}
	
	UpdateNodeHeight(root);
}

static avl_node_t *ToRemove(avl_t *avl, avl_node_t *root, avl_node_t *to_remove, child_pos_t side)
{
	void *tmp_node = NULL;
	
	if (IsLeaf(to_remove))
	{
		root->children[side] = NULL;
		free(to_remove);
	}
	else if (!IS_FULL_PARENT(to_remove))
	{
		if (root == to_remove)
		{
			root->data = to_remove->children[GetChildSide(to_remove)]->data;
		}
		else
		{
			root->children[side] = to_remove->children[GetChildSide(to_remove)];
			free(to_remove);
		}
	
	}
	else
	{
		tmp_node = (FindLowest(to_remove->children[RIGHT]))->data;
		RemoveRec(avl, root, tmp_node);
		to_remove->data = tmp_node;
	}
	
	return root;
}

static avl_node_t *FindRec(const avl_t *avl, avl_node_t *node, const void *key)
{
	if (NULL == node)
	{
		return NULL;
	}
	else if (0 == avl->cmp_func(node->data, key))
	{
		return node;
	}
	
	if (0 < avl->cmp_func(node->data, key))
	{
		return FindRec(avl, node->children[LEFT], key);
	}
	else
	{
		return FindRec(avl, node->children[RIGHT], key);
	}
}

static int ForEachInOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param)
{
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	if (FAILURE == ForEachInOrder(node->children[LEFT], action_func, param))
	{
		return FAILURE;
	}
	
	if (FAILURE == action_func(node->data, param))
	{
		return FAILURE;
	}
		
	if (FAILURE == ForEachInOrder(node->children[RIGHT], action_func, param))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}
	
static int ForEachPostOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param)
{
	if (NULL == node)
	{
		return SUCCESS;
	}
	
	if (FAILURE == ForEachInOrder(node->children[LEFT], action_func, param))
	{
		return FAILURE;
	}
	
	if (FAILURE == ForEachInOrder(node->children[RIGHT], action_func, param))
	{
		return FAILURE;
	}
	
	if (FAILURE == action_func(node->data, param))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}

static int ForEachPreOrder(avl_node_t *node, int (*action_func)(void *, void *), void *param)
{
	if (NULL == node)
	{
		return SUCCESS;
	}
	if (FAILURE == action_func(node->data, param))
	{
		return FAILURE;
	}
		
	
	if (FAILURE == ForEachInOrder(node->children[LEFT], action_func, param))
	{
		return FAILURE;
	}
	
	if (FAILURE == ForEachInOrder(node->children[RIGHT], action_func, param))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}
	

static size_t CountRec(avl_node_t *node)
{
	if (NULL == node)
	{
		return (size_t)0;
	}
	
	return CountRec(node->children[LEFT]) + CountRec(node->children[RIGHT]) + 1;
}
	
static avl_node_t *CreateLeaf(avl_node_t *node, void *data, size_t height)
{
	node->data = data;
	node->height = height;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	return node;
}

static int IsLeaf(avl_node_t *node)
{
	return NULL == node->children[LEFT] && NULL == node->children[RIGHT];
}

static child_pos_t GetChildSide(avl_node_t *node)
{
	if (NULL != node->children[LEFT])
	{
		return LEFT;
	}
	
	if (NULL != node->children[RIGHT])
	{
		return RIGHT;
	}
	
	return NO_CHILD;
}

static avl_node_t *FindLowest(avl_node_t *root)
{
	if (NULL == root->children[LEFT])
	{
		return root;
	}
	
	return FindLowest(root->children[LEFT]);
}

static size_t GetNodeHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return node->height;
}

static int GetNodeBalance(avl_node_t *node)
{
	return (int)GetNodeHeight(node->children[LEFT]) - (int)GetNodeHeight(node->children[RIGHT]);
}

static void Rebalance(avl_node_t *node, int balance)
{
    if (1 < balance)
    {
        if (0 > GetNodeBalance(node->children[LEFT]))
        {
           LeftRotate(node->children[LEFT]);
        }
        RightRotate(node);
    }
    else if (-1 > balance)
    {
        if (0 < GetNodeBalance(node->children[RIGHT]))
        {
            RightRotate(node->children[RIGHT]);
        }
        LeftRotate(node);
    }
}

static void LeftRotate(avl_node_t *node)
{
	avl_node_t *new_root = node->children[RIGHT];
	void *temp_data = node->data;
	
	node->children[RIGHT] = new_root->children[RIGHT];
	new_root->children[RIGHT] = new_root->children[LEFT];
	new_root->children[LEFT] = node->children[LEFT];
	node->data = new_root->data;
	node->children[LEFT] = new_root;
	new_root->data = temp_data;
	
	UpdateNodeHeight(node);
    UpdateNodeHeight(new_root);
}

static void RightRotate(avl_node_t *node)
{
	avl_node_t *new_root = node->children[LEFT];
	void *temp_data = node->data;
	
	node->children[LEFT] = new_root->children[LEFT];
	new_root->children[LEFT] = new_root->children[RIGHT];
	new_root->children[RIGHT] = node->children[RIGHT];
	node->data = new_root->data;
	node->children[RIGHT] = new_root;
	new_root->data = temp_data;
	
    UpdateNodeHeight(new_root);
	UpdateNodeHeight(node);
}

static void UpdateNodeHeight(avl_node_t *node)
{
    int left_height = GetNodeHeight(node->children[LEFT]);
    int right_height = GetNodeHeight(node->children[RIGHT]);

    node->height = 1 + MAX_2(left_height, right_height);
}
