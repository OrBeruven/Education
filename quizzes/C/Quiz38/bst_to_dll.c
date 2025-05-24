#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int status  = 0;
typedef struct bst_node node_t;

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct bst_node
{
	node_t *parent;
	node_t *children[NUM_OF_CHILDREN];
	void *data;
};
node_t *BSTTosortedList(node_t *root);
static void BSTTosortedListRec(node_t *root, node_t **next, node_t **prev);
node_t *CreateNode(void *data);

int main()
{
    int index10 = 10;
    int index8 = 8;
    int index6 = 6;
    int index4 = 4;
    int index14 = 14;
    int index12 = 12;
    int index16 = 16;

    node_t *node1 = CreateNode(&index10);
    node_t *node2 = CreateNode(&index8);
    node_t *node3 = CreateNode(&index6);
    node_t *node4 = CreateNode(&index4);
    node_t *node5 = CreateNode(&index14);
    node_t *node6 = CreateNode(&index12);
    node_t *node7 = CreateNode(&index16);
    node_t *runner = NULL;
	node_t *destroy = NULL;
    node1->children[LEFT] = node3;
    node1->children[RIGHT] = node5;

    node2->parent = node3;

    node3->children[LEFT] = node4;
    node3->children[RIGHT] = node2;
    node3->parent = node1;

    node4->parent = node3;

    node6->parent = node5;

    node7->parent = node5;

    node5->children[LEFT] = node6;
    node5->children[RIGHT] = node7;
    node5->parent = node1;

    node1 = BSTTosortedList(node1);
    runner = node1;
    while (NULL != runner)
    {
        printf("%d ->", *(int *)runner->data);
		destroy = runner;
        runner = runner->children[RIGHT];
		free(destroy);
    }

    return 0;
}

node_t *CreateNode(void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));

	if (NULL == new_node)
	{
		return NULL;
	}
    new_node->data = data;
    new_node->children[RIGHT] = NULL;
    new_node->children[LEFT] = NULL;
    new_node->parent = NULL;
	return new_node;
}

node_t *BSTTosortedList(node_t *root)
{	
	node_t *head = NULL;
	node_t *tail = NULL;
	BSTTosortedListRec(root, &head, &tail);
	
	return head;
}


static void BSTTosortedListRec(node_t *root, node_t **next, node_t **prev)
{
	if (NULL == root)
	{
		return;
	}	
	
	BSTTosortedListRec(root->children[LEFT], next, prev);
	
	if (NULL == *next)
	{
		*next = root;
	}
	
	root->children[LEFT] = *prev;
	if (NULL != *prev)
	{
		(*prev)->children[RIGHT] = root;
	}
	
	*prev = root;
	
	BSTTosortedListRec(root->children[RIGHT], next, prev);
}

