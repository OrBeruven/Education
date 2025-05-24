/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Compile With = "gd print_tree_by_level.c ../../ds/src/queue.c -I../../ds/include"

*****************************/
#include <stdio.h>	/*printf*/
#include <stdlib.h> /*free, malloc*/

#include "utilitiestwo.h"
#include "queue.h"

#define SUCCESS 0
#define FAIL 1

typedef struct bst_node bst_t;

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

struct bst_node
{
	bst_t *parent;
	bst_t *children[NUM_OF_CHILDREN];
	void *data;
};

/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/
void LevelBLevelPrint(bst_t *tree, queue_t *queue);

/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
void TreeEnqueueChildren(bst_t *tree, queue_t *que);

bst_t *CreateNode(void *data);

/*******************************************************************************

*******************************************************************************/
int main(void)
{
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;

    queue_t *que = QueueCreate();

    bst_t *node1 = CreateNode(&num1);
    bst_t *node2 = CreateNode(&num2);
    bst_t *node3 = CreateNode(&num3);
    bst_t *node4 = CreateNode(&num4);
    bst_t *node5 = CreateNode(&num5);

    node1->children[LEFT] = node2;
    node1->children[RIGHT] = node3;
    node2->parent = node1;
    node3->parent = node1;

    node2->children[LEFT] = node4;
    node2->children[RIGHT] = node5;
    node4->parent = node2;
    node5->parent = node5;

    LevelBLevelPrint(node1, que);

    QueueDestroy(que);
    
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);

    return 0;
}

/*******************************************************************************
                    Test Function Implementation
*******************************************************************************/
void LevelBLevelPrint(bst_t *tree, queue_t *queue)
{
    bst_t *data = NULL;
    QueueEnqueue(queue, tree);

    while (!QueueIsEmpty(queue))
    {
        data = QueuePeek(queue);
        QueueDequeue(queue);

        TreeEnqueueChildren(data, queue);
        printf("%d, ", *(int *)data->data);
    }
}

void TreeEnqueueChildren(bst_t *tree, queue_t *que)
{
    if (NULL != tree->children[LEFT])
    {
        QueueEnqueue(que, tree->children[LEFT]);
    }

    if (NULL != tree->children[RIGHT])
    {
        QueueEnqueue(que, tree->children[RIGHT]);
    }
}

bst_t *CreateNode(void *data)
{
	bst_t *new_node = (bst_t *)malloc(sizeof(bst_t));

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
/*******************************************************************************

*******************************************************************************/