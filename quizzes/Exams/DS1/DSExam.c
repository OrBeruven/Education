#include <stdio.h>	    /*perror*/
#include <assert.h>     /*assert*/
#include <sys/types.h>  /*size_t*/

#include "../../../ds/include/utilitiestwo.h"

#define IS_LOOP 1
#define ISNT_LOOP 0

#define IS_ITER 1
#define ISNT_ITER 0

#define IS_ON 1
#define IS_OFF 0

#define ROWS (6)
#define COLS (7)

#define ARR_SIZE 1024

typedef struct node node_t;

node_t *Flip(node_t *node);
static void PrintLoop(node_t *head);

int IsLoop(node_t *node);
static node_t *FindLoop(node_t *node);
void OpenLoop(node_t *head);

static size_t ListSize(node_t *head);
static node_t *MoveList(node_t *node, size_t size);


void SeperateIntersect(node_t *node1, node_t *node2);
int IsIntersected(node_t *node1, node_t *node2);

int IsOnMap(int map[ROWS][COLS], size_t rows, size_t cols, size_t row_index, size_t col_index);

static void FlipTest(void);
static void IntersectionTest(void);
static void IsOnMapTest(void);

size_t FindMissing(int arr[]);
static void FindMissTest(void);

struct node
{
    node_t *next;
    void *data;
};

node_t *Flip(node_t *node)
{
    node_t *prev = NULL;
    node_t *next = NULL;

    assert(NULL != node);

    prev = node;
    next = node->next;

    prev->next = NULL;

    while (NULL != next)
    {
        node = next;
        next = node->next;
        node->next = prev;
        prev = node;
    }

    return node;
}

int IsLoop(node_t *node)
{
    node_t *two = node->next;

    while (NULL != two && (two != node && two->next != node))
    {
        node = node->next;
        two = two->next;
        if (NULL != two)
        {
            two = two->next;
        }
    }

    return NULL == two ? ISNT_LOOP : IS_LOOP;
}

void OpenLoop(node_t *head)
{
    node_t *in_loop = NULL;
    node_t *runner = NULL;

    size_t loop_size = 0;
    size_t i = 0;

    assert(NULL != head);

    in_loop = FindLoop(head);

    if (NULL == in_loop)
    {
        return;
    }

    runner = in_loop->next;
    ++loop_size;

    while (runner != in_loop)
    {
        runner = runner->next;
        ++loop_size;
    }

    runner = head;

    for (i = 1; i < loop_size; ++i)
    {
        runner = runner->next;
    }

    in_loop = head;

    while (runner->next != in_loop)
    {
        in_loop = in_loop->next;
        runner = runner->next;
    }

    runner->next = NULL;
}

int IsIntersected(node_t *node1, node_t *node2)
{
    int diff = 0;
    assert(NULL != node1);
    assert(NULL != node2);

    diff = (int)ListSize(node1) - (int)ListSize(node2);

    if (0 == diff && node1 == node2)
    {
        return IS_ITER;
    }

    if (0 < diff)
    {
        node1 = MoveList(node1, (size_t)diff);
    }
    else
    {
        node2 = MoveList(node2, (size_t)(-1 * diff));
    }

    while (NULL != node1 && node1 != node2)
    {
        node1 = node1->next;
        node2 = node2->next;
    }

    return NULL == node1 ? ISNT_ITER : IS_ITER;
}

void SeperateIntersect(node_t *node1, node_t *node2)
{
    int diff = 0;
    node_t *prev = NULL;

    assert(NULL != node1);
    assert(NULL != node2);

    diff = (int)ListSize(node1) - (int)ListSize(node2);

    if (0 == diff && node1 == node2)
    {
        return;
    }

    if (0 < diff)
    {
        node1 = MoveList(node1, (size_t)diff);
    }
    else
    {
        node2 = MoveList(node2, (size_t)(-1 * diff));
    }

    prev = node1;
    node1 = node1->next;
    node2 = node2->next;

    while (NULL != node1 && node1 != node2)
    {
        prev = node1;
        node1 = node1->next;
        node2 = node2->next;
    }

    prev->next = NULL;
}

int main(void)
{
    printf("Hello World!2\n");
    FlipTest();
    IntersectionTest();
    IsOnMapTest();
    FindMissTest();

    return 0;
}

static node_t *FindLoop(node_t *node)
{
    node_t *two = node->next;

    while (NULL != two && (two != node && two->next != node))
    {
        node = node->next;
        two = two->next;
        if (NULL != two)
        {
            two = two->next;
        }
    }

    return two;
}

static void PrintLoop(node_t *head)
{
	int temp = 10;
	
	while (NULL != head && temp)
	{
		printf("|%d| ->", *(int *) head->data);
		head = head->next;
		--temp;
	}
	printf("\n");
}

static void FlipTest(void)
{
    node_t node_1;
	node_t node_2;
	node_t node_3;
	node_t node_4;
	node_t node_5;
	
	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;
	int num_4 = 4;
	int num_5 = 5;
	
	int status = 0;
	
	
	node_1.data = (void *)&num_1;
  	node_1.next = &node_2;
  	
  	node_2.data = (void *)&num_2;
  	node_2.next = &node_3;
  	
  	node_3.data = (void *)&num_3;
  	node_3.next = &node_4;
  	
  	node_4.data = (void *)&num_4;
  	node_4.next = &node_5;
  	
  	node_5.data = (void *)&num_5;
  	node_5.next = NULL;
    printf("Flip Test : \n");
  	PrintLoop(&node_1);
    PrintLoop(Flip(&node_1));
    PrintLoop(Flip(&node_5));
    PrintLoop(&node_1);

    printf("Loop Test : \n");
  	status = IsLoop(&node_1);
  	PrintLoop(&node_1);
  	RESULT_STATUS(status, 0, );
  	
  	node_5.next = &node_1;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 1, );
    OpenLoop(&node_1);	
    PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 0,);
  	
  	node_5.next = &node_2;

  	
  	status = IsLoop(&node_1);
  	PrintLoop(&node_1);
  	RESULT_STATUS(status, 1,);
  	OpenLoop(&node_1);	
  	status = IsLoop(&node_1);
  	PrintLoop(&node_1);
  	RESULT_STATUS(status, 0,);
  	
  	node_5.next = &node_3;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 1,);
  	OpenLoop(&node_1);	
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 0,);
  	
  	node_5.next = &node_4;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 1,);
  	OpenLoop(&node_1);
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 0,);
  	
  	node_5.next = &node_5;
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 1,);
  	OpenLoop(&node_1);	
  	PrintLoop(&node_1);
  	status = IsLoop(&node_1);
  	RESULT_STATUS(status, 0,);
}

static void IntersectionTest(void)
{
    node_t node_1;
	node_t node_2;
	node_t node_3;
	node_t node_4;
	node_t node_5;
	
    node_t node_6;
	node_t node_7;
	node_t node_8;
	node_t node_9;
	node_t node_10;

	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;
	int num_4 = 4;
	int num_5 = 5;

    int num_6 = 6;
	int num_7 = 7;
	int num_8 = 8;
	int num_9 = 9;
	int num_10 = 10;

    node_1.data = (void *)&num_1;
  	node_1.next = &node_2;
  	node_2.data = (void *)&num_2;
  	node_2.next = &node_3;
  	node_3.data = (void *)&num_3;
  	node_3.next = &node_4;
  	node_4.data = (void *)&num_4;
  	node_4.next = &node_5;
  	node_5.data = (void *)&num_5;
  	node_5.next = NULL;
/**************************************/
    node_6.data = (void *)&num_6;
  	node_6.next = &node_7;
  	
  	node_7.data = (void *)&num_7;
  	node_7.next = &node_8;
  	
  	node_8.data = (void *)&num_8;
  	node_8.next = &node_9;
  	
  	node_9.data = (void *)&num_9;
  	node_9.next = &node_10;
  	
  	node_10.data = (void *)&num_10;
  	node_10.next = NULL;
    printf("\nIntersection Test : \n");
    RESULT_STATUS(IsIntersected(&node_1, &node_6), ISNT_ITER,);

    node_9.next = &node_3;
    PrintLoop(&node_1);
    PrintLoop(&node_6);
    RESULT_STATUS(IsIntersected(&node_1, &node_6), IS_ITER,);
    SeperateIntersect(&node_1, &node_6);
    RESULT_STATUS(IsIntersected(&node_1, &node_6), ISNT_ITER,);
}

static void IsOnMapTest(void)
{
    int x = 0;
	int y = 0;
	int bitmap[ROWS][COLS] = {

		{0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,0,0}
	};

    printf("\nTesting Is On Map\n");
    x = 2;
    y = 3;
	RESULT_STATUS(IsOnMap(bitmap, ROWS, COLS, x, y), IS_ON, Is On Map);

    x = 0;
    y = 3;
    RESULT_STATUS(IsOnMap(bitmap, ROWS, COLS, x, y), IS_OFF, Is Not On Map);
}

static size_t ListSize(node_t *head)
{
    size_t count = 0;

    while (NULL != head)
    {
        head = head->next;
        ++count;
    }

    return count;
}

static node_t *MoveList(node_t *node, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        node = node->next;
    }

    return node;
}

int IsOnMap(int map[ROWS][COLS], size_t rows, size_t cols, size_t row_index, size_t col_index)
{
    ssize_t i = 0;

    for (i = row_index; i >= 0; --i)
    {
        if (1 == map[i][col_index])
        {
            break;
        }
    }
    if (0 == i)
    {
        return IS_OFF;
    }

    for (i = row_index; i < (ssize_t)rows; ++i)
    {
        if (1 == map[i][col_index])
        {
            break;
        }
    }
    if ((ssize_t)rows == i)
    {
        return IS_OFF;
    }

    for (i = col_index; i >= 0; --i)
    {
        if (1 == map[row_index][i])
        {
            break;
        }
    }
    if (0 == i)
    {
        return IS_OFF;
    }

    for (i = col_index; i < (ssize_t)cols; ++i)
    {
        if (1 == map[row_index][i])
        {
            break;
        }
    }
    if ((ssize_t)cols == i)
    {
        return IS_OFF;
    }

    return IS_ON;
}

size_t FindMissing(int arr[])
{
    size_t full = 0;
    size_t miss = 0;
    size_t i = 0;

    for (i = 0; i < ARR_SIZE; ++i)
    {
        full += i;
        miss += arr[i];
    }

    return full - miss;
}

static void FindMissTest(void)
{
    int arr[ARR_SIZE] = {0};
    int i = 0;

    for (i = 0; i < ARR_SIZE; ++i)
    {
        if (i == 22)
        {
            continue;
        }

        arr[i] = i;

        printf("%d, ", arr[i]);
    }
    printf("\nFindMissing Question 8\n");
    RESULT_STATUS(FindMissing(arr), 22, FindMissing);
}
