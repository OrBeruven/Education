/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>
#include "../../ds/include/bst.h"

static void SwapChildren(bst_node_t *node);
void MirrorTree(bst_t *bst);
void MirrorRec(bst_node_t *root);
static void TomerPrintTree(bst_node_t *node, int level);
int CmpFunc(const void *a, const void *b);

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


static void SwapChildren(bst_node_t *node)
{
	bst_node_t *temp = node->children[LEFT];
	node->children[LEFT] = node->children[RIGHT];
	node->children[RIGHT] = temp;
}

void MirrorTree(bst_t *bst)
{
	MirrorRec(bst->dummy_root.children[LEFT]);
}

void MirrorRec(bst_node_t *root)
{
	if (NULL == root->children[LEFT] && NULL == root->children[RIGHT])
	{
		return;
	}
	
	if (NULL != root->children[LEFT])
	{
		MirrorRec(root->children[LEFT]);
	}
	
	SwapChildren(root);

	if (NULL != root->children[LEFT])
	{
		MirrorRec(root->children[LEFT]);
	}
	
	return;
}

int main(void)
{
	bst_t *bst = NULL;
	int num1 = 5;
	int num2 = 3;
	int num3 = 7;
	int num4 = 2;
	int num5 = 4;
	int num6 = 6;
	int num7 = 8;
	
	bst = BSTCreate(CmpFunc);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num7);
	
	TomerPrintTree(bst->dummy_root.children[LEFT], 0);
	MirrorTree(bst);
	TomerPrintTree(bst->dummy_root.children[LEFT], 0);
	
	
	BSTDestroy(bst);
	
	return 0;
}

int CmpFunc(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

static void TomerPrintTree(bst_node_t *node, int level)
{
	int i = 0;
	if (NULL == node) return;

	TomerPrintTree(node->children[RIGHT], level + 1);
	for (i = 0 ; i < level ; ++i)
	{
        printf("    	");
	}
	printf("%d\n", *(int*)node->data);
	TomerPrintTree(node->children[LEFT], level + 1);
}
