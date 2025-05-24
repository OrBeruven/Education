/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File for  Test

*****************************/
#include <stdio.h>	/*printf*/
#include <assert.h>	/*assert*/
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define SUCCESS 0
#define FAIL 1
#define STACK_SIZE 10
#define ASCII 256

#define LEFT 0
#define RIGHT 1

#define MAX_WORD_LENGTH (30)
#define NUM_OF_LINES (104334)

typedef struct bst_node bst_node_t;

typedef struct node
{
	int *data;
	struct node *next;
} node_t;

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *left;
    bst_node_t *right;
	int data;
};

/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/

void Q1SLL(void);
void Q2SumSub(void);
void Q3StackSort(void);
void Q4FileSort(void);
void Q5BST(void);
void Q7RevStr(void);
void Q8Permu(void);
void Q10StackInsert(void);

/*******************************************************************************
*******************************************************************************/


/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/

static void PrintSLL(node_t *head);
void PrintStack(stack_t *stack);
static void PrintTree(bst_node_t *node, int level);
static void SwapChar(char *str, int i1, int i2);
void Swap(char *a, char *b);
void PrintArr(char str[], size_t size ,char **dec);
static int CheckDec(char *str ,char **dec);

/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
                    Exam Function Declarations
*******************************************************************************/

node_t *Flip(node_t *curr);
node_t *FlipRec(node_t *prev, node_t *curr);

int SumSubArr(int *arr, size_t size);

stack_t *SortStack(stack_t *st1);

int sort_chars_in_file(const char *file_name, char *result);
static void CountSortBuffer(char *buffer, size_t size);

int BSTInsertIterative(bst_node_t *bst, int input);
int BSTInsertRec(bst_node_t *bst, int input);
bst_node_t *CreateNode(bst_node_t *parent, int input, int side);

void ReverseString(char *str);
static void RevRec(char *str, int lhs, int rhs);

void PrintPermutations(char str[], size_t size, size_t start, char **dec);

void RecInsertStack(stack_t *st, int input);

/*******************************************************************************
*******************************************************************************/

int main(void)
{
     /* Q1SLL();
    Q2SumSub(); 
    Q3StackSort();
    Q4FileSort();
    Q5BST();
    Q7RevStr();*/
    Q8Permu();

    /*Q10StackInsert();*/
    return 0;
}

/*******************************************************************************
                    Test Function Implementation
*******************************************************************************/
void Q1SLL(void)
{
    node_t node_1;
	node_t node_2;
	node_t node_3;
	node_t node_4;
	node_t node_5;
	node_t *head = &node_1;
	
	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;
	int num_4 = 4;
	int num_5 = 5;
	
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
  	
  	PrintSLL(head);
    printf("\n\n");
    PrintSLL(FlipRec(NULL, head));
}

void Q2SumSub(void)
{
    int arr[9] = {-2, 8, -3, 4, -1, 2, 1, -5, 4};
    printf("\nQ2 biggest sum = %d\n", SumSubArr(arr, 9));
}

void Q3StackSort(void)
{
    int num1 = 1;
    int num2 = 0;
    int num3 = 6;
    int num4 = 4;
    int num5 = 5;
    int num6 = 2;
    int num7 = 3;
    stack_t *stack = StackCreate(STACK_SIZE, sizeof(int));
    stack_t *temp_stack = NULL;

    StackPush(stack, &num1);
    StackPush(stack, &num2);
    StackPush(stack, &num3);
    StackPush(stack, &num4);
    StackPush(stack, &num5);
    StackPush(stack, &num6);
    StackPush(stack, &num7);

    PrintStack(stack);
    temp_stack = SortStack(stack);
    PrintStack(temp_stack);
    printf("\n");

    StackDestroy(temp_stack);
    StackDestroy(stack);
}

void Q4FileSort(void)
{
    char buffer[50] = {0};
    sort_chars_in_file("./text.txt", buffer);
    printf("%s", buffer);
}

void Q5BST(void)
{
    bst_node_t *b10 = (bst_node_t *)malloc(sizeof(bst_node_t));
    bst_node_t *b5 = (bst_node_t *)malloc(sizeof(bst_node_t));
    bst_node_t *b15 = (bst_node_t *)malloc(sizeof(bst_node_t));
    bst_node_t *b1 = (bst_node_t *)malloc(sizeof(bst_node_t));
    bst_node_t *b9 = (bst_node_t *)malloc(sizeof(bst_node_t));

    b10->data = 10;
    b10->parent = NULL;
    b10->left = b5;
    b10->right = b15;

    b5->data = 5;
    b5->parent = b10;
    b5->left = b1;
    b5->right = b9;

    b15->data = 15;
    b15->parent = b10;
    b15->left = NULL;
    b15->right = NULL;
    
    b1->data = 1;
    b1->parent = b5;
    b1->left = NULL;
    b1->right = NULL;

    b9->data = 9;
    b9->parent = b5;
    b9->left = NULL;
    b9->right = NULL;


    /* BSTInsertIterative(b10, 8); */
    BSTInsertRec(b10, 8);


    PrintTree(b10, 0);
    free(b10);
    free(b5);
    free(b15);
    free(b1);
    free(b9);
}

void Q7RevStr(void)
{
    char str[7] = "string";
    ReverseString(str);
    printf("%s\n", str);
}

void Q8Permu(void)
{
    char arr[] = "eat";
	char **dec = (char **)malloc(NUM_OF_LINES * sizeof(char *));
	char word[MAX_WORD_LENGTH];
	char *file_name = "/usr/share/dict/words";
	FILE *file = fopen(file_name, "r");
	char *str = NULL;
	size_t i = 0;
	size_t size = strlen(arr);
	size_t word_len = 0;

	if (NULL == file)
	{
		printf("Error opening file!\n");
		return;
	}

	if (NULL == dec)
	{
		printf("Error alloc buffer\n");
		return;
	}

	while (fgets(word, MAX_WORD_LENGTH, file))
	{
		word_len = strlen(word);
		if (word_len > 0 && '\n' == word[word_len - 1])
		{
			word[word_len - 1] = '\0';
		}

		str = word;

		dec[i] = malloc(word_len);
		if (NULL == dec[i])
		{
			printf("dec[%ld] failed\n", i);
			return;
		}
		strncpy(dec[i], str, word_len);	

		++i;
	}

	PrintPermutations(arr, size, 0,dec);

	for (i = 0; i < NUM_OF_LINES; ++i)
	{
		free(dec[i]);
	}

	fclose(file);
	free(dec);
}

void Q10StackInsert(void)
{
    int num1 = 1;
    int num2 = 0;
    int num3 = 6;
    int num4 = 4;
    int num5 = 5;
    int num6 = 2;
    int num7 = 3;
    stack_t *stack = StackCreate(STACK_SIZE, sizeof(int));
    stack_t *temp_stack = NULL;

    StackPush(stack, &num1);
    StackPush(stack, &num2);
    StackPush(stack, &num3);
    StackPush(stack, &num4);
    StackPush(stack, &num6);
    StackPush(stack, &num7);

    PrintStack(stack);
    temp_stack = SortStack(stack);
    printf("\n");

    RecInsertStack(temp_stack, num5);
    PrintStack(temp_stack);

    StackDestroy(temp_stack);
    StackDestroy(stack);
}
/*******************************************************************************
                    Exam Function Implementation
*******************************************************************************/
node_t *Flip(node_t *curr)
{
    node_t *prev = NULL;
    node_t *next = curr->next;

    while (NULL != next)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }

    curr->next = prev;

    return curr;
}

node_t *FlipRec(node_t *prev, node_t *curr)
{
    node_t *to_ret = NULL;

    if (NULL == curr->next)
    {
        curr->next = prev;
        return curr;
    }

    to_ret = FlipRec(curr, curr->next);

    curr->next = prev;
    return to_ret;
}

int SumSubArr(int *arr, size_t size)
{
    int sum = 0;
    int middle_sum = 0;
    int i = 0;

    for (i = 0; i < (int)size; ++i)
    {
        middle_sum += arr[i];

        if (0 > middle_sum)
        {
            middle_sum = 0;
        }
        else if (middle_sum > sum)
        {
            sum = middle_sum;
        }
    }

    return sum;
}

stack_t *SortStack(stack_t *st1)
{
    int temp = 0;

    stack_t *st2 = StackCreate(STACK_SIZE, sizeof(int));
    if (NULL == st2)
    {
        return NULL;
    }

    while (!StackIsEmpty(st1))
    {
        temp = *(int *)StackPeek(st1);
        StackPop(st1);

        while (!StackIsEmpty(st2) && (temp > *(int *)StackPeek(st2)))
        {
            StackPush(st1, StackPeek(st2));
            StackPop(st2);
        }

        StackPush(st2, &temp);
    }

    return st2;
}

int sort_chars_in_file(const char *file_name, char *result)
{
    size_t size = 0;
    FILE *fd = fopen(file_name, "r");
    if (NULL == fd)
    {
        return FAIL;
    }

    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    fread(result, sizeof(char), size, fd);

    CountSortBuffer(result, size);
    return SUCCESS; 
}

int BSTInsertIterative(bst_node_t *bst, int input)
{
    bst_node_t *iter = bst;
    int side = LEFT;

    while (NULL != iter)
    {
        bst = iter;
        
        if (iter->data < input)
        {
            side = RIGHT;
            iter = iter->right;
        }
        else
        {
            side = LEFT;
            iter = iter->left;
        }
    }

    return NULL == CreateNode(bst, input, side) ? FAIL : SUCCESS;
}

int BSTInsertRec(bst_node_t *bst, int input)
{
    if (bst->data < input)
    {
        if (NULL == bst->right)
        {
            return NULL == CreateNode(bst, input, RIGHT);
        }
        else
        {
            return BSTInsertRec(bst->right, input);
        }
    }
    else
    {
        if (NULL == bst->left)
        {
            return NULL == CreateNode(bst, input, LEFT);
        }
        else
        {
            return BSTInsertRec(bst->left, input);
        }
    }
}

void ReverseString(char *str)
{
    RevRec(str, 0, strlen(str) - 1);
}

static void RevRec(char *str, int lhs, int rhs)
{
    if (lhs >= rhs)
    {
        return;
    }

    SwapChar(str, lhs, rhs);
    RevRec(str, lhs + 1, rhs - 1);
}

void PrintPermutations(char str[], size_t size, size_t start, char **dec)
{
    size_t i = 0;

    if (start == size - 1) 
	{
        PrintArr(str, size, dec);
        return;
    }

    for (i = start; i < size; ++i)
    {
        Swap(&str[start], &str[i]);
        PrintPermutations(str, size, start + 1,dec);
        Swap(&str[start], &str[i]);
    }
}

void RecInsertStack(stack_t *st, int input)
{
    int temp = 0;
    if (StackIsEmpty(st) || *(int *)StackPeek(st) > input)
    {
        StackPush(st, &input);
        return;
    }

    temp = *(int *)StackPeek(st);
    StackPop(st);
    RecInsertStack(st, input);
    StackPush(st, &temp);
}
/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
*******************************************************************************/
static void PrintSLL(node_t *head)
{
	if (NULL == head)
	{
		return;
	}
	
	printf("%d -> ", *(int *)head->data);
	
	PrintSLL(head->next);
}	

void PrintStack(stack_t *stack)
{
    stack_t *stack2 = StackCreate(STACK_SIZE, sizeof(int));

    while (1 != StackIsEmpty(stack))
    {
        printf("%d, ", *(int *)StackPeek(stack));
        StackPush(stack2, StackPeek(stack));
        StackPop(stack);
    }
    printf("\n");
    while (1 != StackIsEmpty(stack2))
    {
        StackPush(stack, StackPeek(stack2));
        StackPop(stack2);
    }

    StackDestroy(stack2);
}

static void CountSortBuffer(char *buffer, size_t size)
{
    int lut[ASCII] = {0};
    size_t i = 0;
    size_t buffer_index = 0;

    for (i = 0; i < size; ++i)
    {
        ++lut[(int)buffer[i]];
    }

    for (i = 0; i < ASCII; ++i)
    {
        while (0 < lut[i])
        {
            buffer[buffer_index] = (char)i;
            ++buffer_index;
            --lut[i];
        }
    }
}

bst_node_t *CreateNode(bst_node_t *parent, int input, int side)
{
    bst_node_t *new = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (NULL == new)
    {
        return NULL;
    }

    new->data = input;
    new->left = NULL;
    new->right = NULL;
    new->parent = parent;

    if (LEFT == side)
    {
        parent->left = new;
    }
    else
    {
        parent->right = new;
    }

    return new;
}

static void PrintTree(bst_node_t *node, int level)
{
	int i = 0;
	if (NULL == node) return;

	PrintTree(node->right, level + 1);
	for (i = 0 ; i < level ; ++i)
	{
        printf("    	");
	}
	printf("%d\n", node->data);
	PrintTree(node->left, level + 1);
}

static void SwapChar(char *str, int i1, int i2)
{
    char temp = str[i1];
    str[i1] = str[i2];
    str[i2] = temp;
}

void Swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void PrintArr(char str[], size_t size ,char **dec)
{
	size_t i = 0;
	if (1 == CheckDec(str ,dec))
	{
		for (i = 0; i < size; ++i)
		{
			printf("%c", str[i]);
		}
		puts("");
	}
}

static int CheckDec(char *str ,char **dec)
{
	while (*dec != NULL)
	{
		if (0 == strcmp(str,*dec))
		{
			return 1;
		}
		++dec;
	}
	return 0;
}