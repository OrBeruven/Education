/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 26.03.2023

	Description : c file for AVL Tree Tests

*****************************/

#include <stdio.h>

#include "avl.h"
#include "utilitiestwo.h"

typedef enum child_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
}child_pos_t;

typedef struct avl_node avl_node_t;

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

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateDestroyTest(void);

static void InsertTest(void);

static void FindTest(void);

static void ForEachTest(void);

static void IsEmptyTest(void);

static void CountTest(void);

static void HeightTest(void);

static void HeightFactorTest(void);

static void RemoveTest(void);

/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
						Help function declarations
*******************************************************************************/
int CmpFunc(const void *a, const void *b);

int AuctionFunc(void *a, void *b);

static void TomerPrintTree(avl_node_t *node, int level);
/*******************************************************************************
*******************************************************************************/

int main(void)
{
	HEADER(Testing Create and Destroy);
	CreateDestroyTest();
	printf("\n");	
	
	HEADER(Testing Insert);
	InsertTest();
	printf("\n");
	
	HEADER(Testing Find);
	FindTest();
	printf("\n");
	
	ForEachTest();
	printf("\n");
	
	HEADER(Testing IsEmpty);
	IsEmptyTest();
	printf("\n");
	
	HEADER(Testing Count);
	CountTest();
	printf("\n");
	
	HEADER(Testing Height);
	HeightTest();
	printf("\n");
	
	HEADER(Testing HeightFactor);
	HeightFactorTest();
	printf("\n");
	
	HEADER(Testing Remove);
	RemoveTest();
	printf("\n");
	
	return 0;
}

/**************************************************************************************
								Test Functions
**************************************************************************************/
static void CreateDestroyTest(void)
{	
	avl_t *avl = NULL;
	int num1 = 100;
	
	RESULT_STATUS(avl == NULL, 1, BeforeCreation);
	
	avl = AVLCreate(CmpFunc);
	
	RESULT_STATUS(avl == NULL, 0, Creation);
	
	AVLInsert(avl, &num1);
	
	AVLDestroy(avl);
}

static void InsertTest(void)
{
	int num1 = 100;
	int num2 = 150;
	int num3 = 50;
	int num4 = 200;
	int num5 = 125;
	int num6 = 250;
	int num7 = 175;
	avl_t *avl = AVLCreate(CmpFunc);
	avl_node_t *runner = NULL;
	
	runner = avl->dummy_root.children[0];
	
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	runner = avl->dummy_root.children[0];
	RESULT_STATUS(*(int *)runner->data, 100, Root Before Balance);
	AVLInsert(avl, &num6);
	runner = avl->dummy_root.children[0];
	RESULT_STATUS(*(int *)runner->data, 150, Root After Balance);
	AVLInsert(avl, &num7);
	
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	
	
	RESULT_STATUS(AVLCount(avl), 7, Count);
	
	AVLDestroy(avl);
}

static void FindTest(void)
{
	int num1 = 100;
	int num2 = 150;
	int num3 = 50;
	int num4 = 200;
	int num5 = 125;
	int num6 = 250;
	int num7 = 175;
	int num8 = 1;
	avl_t *avl = AVLCreate(CmpFunc);
	
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num6);
	AVLInsert(avl, &num7);
	
	RESULT_STATUS(*(int *)AVLFind(avl, &num4), 200, Finding by key);
	RESULT_STATUS(*(int *)AVLFind(avl, &num7), 175,);
	RESULT_STATUS(*(int *)AVLFind(avl, &num3), 50,);
	RESULT_STATUS(*(int *)AVLFind(avl, &num5), 125,);
	RESULT_STATUS(NULL == AVLFind(avl, &num8), 1, Searching missing key);
	
	AVLDestroy(avl);
}

static void ForEachTest(void)
{
	int num1 = 100;
	int num2 = 150;
	int num3 = 50;
	int num4 = 200;
	int num5 = 125;
	int num6 = 250;
	int num7 = 175;
	avl_t *avl = AVLCreate(CmpFunc);
	
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num6);
	AVLInsert(avl, &num7);
	
	HEADER(The Tree Look Like :);
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	
	HEADER(ForEach IN_ORDER);
	AVLForEach(avl, AuctionFunc, NULL, IN_ORDER);
	printf("\n");
	
	HEADER(ForEach POST_ORDER);
	AVLForEach(avl, AuctionFunc, NULL, POST_ORDER);
	printf("\n");
	
	HEADER(ForEach PRE_ORDER);
	AVLForEach(avl, AuctionFunc, NULL, PRE_ORDER);
	AVLDestroy(avl);
}

static void IsEmptyTest(void)
{
	int num1 = 100;
	int num2 = 150;
	
	avl_t *avl = AVLCreate(CmpFunc);

	RESULT_STATUS(AVLIsEmpty(avl), 1, Empty AVL Tree);
	AVLInsert(avl, &num1);
	RESULT_STATUS(AVLIsEmpty(avl), 0, No Empty AVL Tree);
	
	AVLInsert(avl, &num2);
	AVLRemove(avl, &num2);
	
	RESULT_STATUS(AVLIsEmpty(avl), 0, );
	AVLRemove(avl, &num1);

	RESULT_STATUS(AVLIsEmpty(avl), 1, AfterRemove);
	
	AVLDestroy(avl);
}

static void CountTest(void)
{
	int num1 = 100;
	int num2 = 150;
	int num3 = 50;
	int num4 = 200;
	int num5 = 125;
	int num6 = 250;
	int num7 = 175;
	avl_t *avl = AVLCreate(CmpFunc);
	
	
	RESULT_STATUS(AVLCount(avl), 0, Counting Empty Tree);
	AVLInsert(avl, &num1);
	RESULT_STATUS(AVLCount(avl), 1, Counting Tree);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num4);
	RESULT_STATUS(AVLCount(avl), 4, );
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num6);
	RESULT_STATUS(AVLCount(avl), 6, );
	AVLInsert(avl, &num7);
	RESULT_STATUS(AVLCount(avl), 7, );
	
	AVLRemove(avl, &num4);
	RESULT_STATUS(AVLCount(avl), 6, );
	
	AVLRemove(avl, &num3);
	RESULT_STATUS(AVLCount(avl), 5, );
	AVLDestroy(avl);
}	

static void HeightTest(void)
{
	int num1 = 100;
	int num2 = 150;
	int num3 = 50;
	int num4 = 200;
	int num5 = 125;
	int num6 = 250;
	int num7 = 175;
	avl_t *avl = AVLCreate(CmpFunc);
	
	RESULT_STATUS(AVLHeight(avl), 0, Height);
	AVLInsert(avl, &num1);
	RESULT_STATUS(AVLHeight(avl), 1, );
	AVLInsert(avl, &num2);
	RESULT_STATUS(AVLHeight(avl), 2, );
	AVLInsert(avl, &num3);
	RESULT_STATUS(AVLHeight(avl), 2, );
	AVLInsert(avl, &num4);
	RESULT_STATUS(AVLHeight(avl), 3, );
	AVLInsert(avl, &num5);
	
	
	AVLInsert(avl, &num6);
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	printf("\n\n\n");
	RESULT_STATUS(AVLHeight(avl), 3, Should stay 3 because of balance);
	AVLInsert(avl, &num7);
	
	AVLDestroy(avl);
}

static void HeightFactorTest(void)
{
	int num1 = 100;
	int num2 = 50;
	int num3 = 25;
	int num4 = 20;
	int num5 = 35;
	int num6 = 30;
	avl_t *avl = AVLCreate(CmpFunc);
	avl_node_t *runner = NULL;
	
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	
	printf("\n\n\n");
	AVLInsert(avl, &num6);
	
	runner = avl->dummy_root.children[LEFT];
	runner = runner->children[LEFT];
	runner = runner->children[LEFT];
	RESULT_STATUS(avl->dummy_root.children[LEFT]->height, 3, Height After Insert);
	printf("\n\n");	
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	
	AVLDestroy(avl);
}

static void RemoveTest(void)
{
	int num1 = 100;
	int num2 = 50;
	int num3 = 25;
	int num4 = 20;
	int num5 = 35;
	int num6 = 30;
	avl_t *avl = AVLCreate(CmpFunc);
	
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num6);
	
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	
	printf("\n\n");
	AVLRemove(avl, &num5);	
	
	RESULT_STATUS(*(int *)avl->dummy_root.children[LEFT]->data != 35, 1, Removing 35);
	printf("\n\n");	
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	printf("\n\n");		
	AVLRemove(avl, &num1);
	RESULT_STATUS(*(int *)avl->dummy_root.children[LEFT]->data != 100, 1, Removing 100 for balance);
	printf("\n\n");	
	TomerPrintTree(avl->dummy_root.children[LEFT], 0);
	AVLDestroy(avl);
}
/**************************************************************************************
								Help Functions
**************************************************************************************/
int CmpFunc(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int AuctionFunc(void *a, void *b)
{
	(void)b;
	printf("%d -> ", *(int *)a);
	return 0;
}

static void TomerPrintTree(avl_node_t *node, int level)
{
	int i = 0;
	if (NULL == node) return;

	TomerPrintTree(node->children[RIGHT], level + 1);
	for (i = 0 ; i < level ; ++i)
	{
        printf("    	");
	}
	printf("%d, %ld\n", *(int*)node->data, node->height);
	TomerPrintTree(node->children[LEFT], level + 1);
}
