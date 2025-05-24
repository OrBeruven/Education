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

#define TEST(condition, func_name) ((1) == (condition))?\
                                    printf("%-20s:\x1b[32m Success \x1b[0m\n", #func_name) : \
                                     printf("%-20s:\x1b[1;31m Failure, Line: %d \x1b[0m\n",\
                                     #func_name, __LINE__)
                                     
#define HEADER(func_name) (printf("\n\t\033[4;36m %s \033[0m\n", #func_name));

/*******************************************************************************
                    Help Structures
*******************************************************************************/
typedef struct doubly_linked_list dll_t;
typedef struct node *iterator_t;
typedef struct node node_t;

typedef struct bst_node bst_node_t;
typedef struct stack stack_t;

enum CHILDREN_NUM {RIGHT, LEFT, CHILDRENS};

struct doubly_linked_list
{
	node_t *head;
	node_t *tail;
};

struct node
{
	void *data;
	node_t *next;
	node_t *prev;
};

struct bst_node
{
	bst_node_t *children[CHILDRENS];
	void *data;
};

struct stack {
	void *data;
	size_t top;
	size_t capacity;
	size_t i_size;
};

typedef struct min_stack
{
    stack_t *stack;
    stack_t *min_stack;
} min_stack_t;

typedef struct int_array
{
    int *arr;
    int *count_arr;
    int counter;
    int all_val;
} int_array_t;

/**************** STACK & BST FUNCTIONS ****************/

stack_t *StackCreate(size_t capacity, size_t item_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	if (stack == NULL)
	{
		perror("Allocation error\n");
		return NULL;
	}
	
	stack->data = malloc(capacity * item_size);
	if (stack->data == NULL)
	{
		free(stack);
		perror("Allocation error\n");
		return NULL;
	}
	
	stack->top = 0;
	stack->capacity = capacity;
	stack->i_size = item_size;
	
	return stack;
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->top;
}

void StackPush(stack_t *stack, const void *item)
{
	assert(NULL != stack);
	assert(NULL != item);
	
	memmove((char *)stack->data + (stack->i_size * stack->top), item, stack->i_size);
	stack->top++;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	if (stack->top != 0)
	{
		return 0;
	}
	
	return 1;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	
	if (stack->top != 0)
	{
		stack->top--;
	}
	
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->capacity;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack->data);
	free(stack);
}

void *StackPeek(const stack_t *stack)
{	
	assert(NULL != stack);
	
	return ((void *)((char *)stack->data + ((stack->top- 1) * stack->i_size)));
	
}

static bst_node_t *Create(void *data)
{
    bst_node_t *node = malloc(sizeof(bst_node_t));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    
    return node;
}

static void PrintTree(bst_node_t *node, int level)
{
	int i = 0;
	if (NULL == node) return;

	PrintTree(node->children[RIGHT], level + 1);
	for (i = 0 ; i < level ; ++i)
	{
        printf("    	");
	}
	printf("%d\n", *(int *)node->data);
	PrintTree(node->children[LEFT], level + 1);
}


/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/

void Test2(void);
void Test3(void);
void Test4(void);
void Test5(void);
void Test7(void);
void Test8(void);
void Test9(void);
void Test13(void);
void Test13b(void);

/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
                    Exam Function Declarations
*******************************************************************************/
/*********Question 1 *********/
void SetVal(int_array_t *array, int indx, int val);
void SetAll(int_array_t *array, int val);
int GetVal(int_array_t *array, int indx);

/*********Question 2 *********/
int IsSumOfTwo(unsigned int *arr, unsigned int sum, int size);

/*********Question 3 *********/
int Find(char *arr, size_t size, char c);

/*********Question 4 *********/
void Rotate(char *arr, int n, int size);
void Reverse(char *arr, char *end);

/*********Question 5 *********/
int NumOfIslands(int arr[8][5], size_t rows, size_t cols);
void ClearOnes(int arr[8][5], size_t rows, size_t cols, int i, int j);
int IsOne(int arr[8][5], size_t rows, size_t cols, int i, int j);

/*********Question 6 *********/
void *MinStackPeek(min_stack_t *stack);
void MinStackPop(min_stack_t *stack);
void *MinStackGetMin(min_stack_t *stack);
void MinStackPush(min_stack_t *stack, void *num);

/*********Question 7 *********/
int CheckParaneth(char *str);

/*********Question 8 *********/
unsigned int MulRec(unsigned int num, unsigned int mul);
unsigned int IncerementRec(unsigned int num);

/*********Question 9 *********/
void PushFront(node_t *pivot, node_t *node);
void PushBehind(node_t *pivot, node_t *node);
void SortDLL(dll_t *dll, node_t *pivot);

/*******************************************************************************
*******************************************************************************/

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
int CmpFunc(const void *x, const void *y);


/*******************************************************************************
*******************************************************************************/

/*****************  Question 1 **************/

int GetVal(int_array_t *array, int indx)
{
   return (array->count_arr[indx] == array->counter) ? 
         array->arr[indx] : array->all_val;
}

void SetAll(int_array_t *array, int val)
{
   ++array->counter;
   array->all_val = val;
}

void SetVal(int_array_t *array, int indx, int val)
{
   array->arr[indx] = val;
   array->count_arr[indx] = array->counter;
}

/*****************  Question 2 **************/

int IsSumOfTwo(unsigned int *arr, unsigned int sum, int size)
{
    int left = 0;
    int right = size - 1;

    qsort(arr, sizeof(unsigned int), size, CmpFunc);

    while (left < right)
    {
        if (arr[left] + arr[right] == sum)
        {
            return 1;
        }
        else if (arr[left] + arr[right] > sum)
        {
            --right;
        }
        else
        {
            ++left;
        }
    }

    return 0;
}

int CmpFunc(const void *x, const void *y)
{
    return *(unsigned int *)x - *(unsigned int *)y;
}

/*****************  Question 3 **************/

int Find(char *arr, size_t size, char c)
{
    size_t num = 1;
    int i = 0;

    for (i = 0; i < (int)size && num != 0; ++i)
    {
        num *= c ^ arr[i];
    }

    return !num;
}

/*****************  Question 4 **************/

void Reverse(char *arr, char *end)
{
    char temp = 0;

    while (arr < end)
    {
        temp = *arr;
        *arr = *end;
        *end = temp;

        ++arr;
        --end;
    }
}

void Rotate(char *arr, int n, int size)
{
    Reverse(arr, arr + size - 1);
    Reverse(arr, arr + n - 1);
    Reverse(arr + n, arr + size - 1);
}

/*****************  Question 5 **************/

int IsOne(int arr[8][5], size_t rows, size_t cols, int i, int j)
{
    if (i < 0 || i >= (int)rows)
    {
        return 0;
    }
    if (j < 0 || j >= (int)cols)
    {
        return 0;
    }

    return arr[i][j];
}

void ClearOnes(int arr[8][5], size_t rows, size_t cols, int i, int j) 
{
    if (IsOne(arr, rows, cols, i, j))
    {
        arr[i][j] = 0;
        ClearOnes(arr, rows, cols, i, j + 1);
        ClearOnes(arr, rows, cols, i + 1, j);
        ClearOnes(arr, rows, cols, i + 1, j + 1);
        ClearOnes(arr, rows, cols, i - 1, j);
        ClearOnes(arr, rows, cols, i, j - 1);
        ClearOnes(arr, rows, cols, i - 1, j - 1);
        ClearOnes(arr, rows, cols, i + 1, j - 1);
        ClearOnes(arr, rows, cols, i - 1, j + 1);
    }
}

int NumOfIslands(int arr[8][5], size_t rows, size_t cols)
{
    int num_of_islands = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < (int)rows; ++i)
    {
        for (j = 0; j < (int)cols; ++j)
        {
            if (arr[i][j] == 1)
            {
                ++num_of_islands;
                ClearOnes(arr, rows, cols, i, j);
            }
        }
    }

    return num_of_islands;
}

/*****************  Question 6 **************/

void *MinStackPeek(min_stack_t *stack)
{
    return StackPeek(stack->stack);
}

void MinStackPop(min_stack_t *stack)
{
    StackPop(stack->min_stack);
    StackPop(stack->stack);
}

void *MinStackGetMin(min_stack_t *stack)
{
    return StackPeek(stack->min_stack);
}

void MinStackPush(min_stack_t *stack, void *num)
{
    if (StackIsEmpty(stack->stack))
    {
        StackPush(stack->min_stack, num);
        
    }
    else if (*(int *)StackPeek(stack->min_stack) < *(int *)num)
    {
        StackPush(stack->min_stack, StackPeek(stack->min_stack));
    }
    else
    {
        StackPush(stack->min_stack, num);
    }

    StackPush(stack->stack, num);
}

/*****************  Question 7 **************/

int CheckParaneth(char *str)
{
    size_t length = strlen(str);
    stack_t *parenth = StackCreate(length / 2, sizeof(char));
    char ch = 0;
    size_t i = 0;
    char curr = 0;

    for (i = 0; i < length; ++i)
    {
        ch = str[i];

        if (ch == '(' || ch == '{' || ch == '<' || ch == '[')
        {
            StackPush(parenth, &ch);
        }
        else if (ch == ')' || ch == '}' || ch == '>' || ch == ']')
        {
            curr = *(char *)StackPeek(parenth);
            if (ch - curr <= 0 || ch - curr > 2)
            {
                return 0;
            }
            StackPop(parenth);
        }
    }

    ch = StackIsEmpty(parenth);
    StackDestroy(parenth);
    return (int)ch;
}

/*****************  Question 8 **************/

unsigned int MulRec(unsigned int num, unsigned int mul)
{
    if (0 == mul)
    {
        return 0;
    }

    return num + (MulRec(num, mul - 1));
}

unsigned int IncerementRec(unsigned int num)
{
    if ((num & 1) == 0)
    {
        return num | 1;
    }

    return IncerementRec((num >> 1) << 1);
}

/*****************  Question 9 **************/
void PrintList(node_t* head) {
    node_t* curr = head;
    while (curr != NULL) {
        printf("%d ", *(int*)curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void Swap(int *x, int*y)
{
    int temp = *x;
    *x = *y;
    *y= temp;
}

/*Mor's solution*/
void PivodDLL(node_t *head, int pivot)
{
    node_t *curr = head;
    node_t *swap = head;

    while (curr != NULL)
    {
        if (*(int *)curr->data >= pivot)
        {
            curr = curr->next;
        }
        else
        {
            Swap(curr->data, swap->data);
            swap = swap->next;
            curr = curr->next;
        }
    }
}

/*My Soulution*/
void PushFront(node_t *pivot, node_t *node)
{
    node->prev = pivot;
    node->next = pivot->next;
    pivot->next->prev = node;
    pivot->next = node;
}

void PushBehind(node_t *pivot, node_t *node)
{
    node->next = pivot;
    node->prev = pivot->prev;
    pivot->prev->next = node;
    pivot->prev = node;
}

void SortDLL(dll_t *dll, node_t *pivot)
{
    node_t *iter = dll->head;
    node_t *temp = NULL;

    while (iter != NULL)
    {
        temp = iter->next;

        if (*(int *)iter->data > *(int *)pivot->data)
        {
            PushFront(pivot, iter);
        }
        else
        {
            PushBehind(pivot, iter);
        }

        iter = temp;
    }
}

/*****************  Question 13 **************/
int InsertIter(bst_node_t *node, void *data)
{
    int pos = 0;
    bst_node_t *curr = node;

    while (curr->data != NULL)
    {
        pos = *(int *)curr->data > *(int *)data;

        if (NULL != curr->children[pos])
        {
            curr = curr->children[pos];
        }
        else
        {
            curr->children[pos] = Create(data);

            return curr->children[pos]->data != NULL;
        }
    }

    return 0;
}

int InsertRec(bst_node_t *node, void *data)
{
    int pos = 0;
    pos = *(int *)node->data > *(int *)data;

    if (NULL == node->children[pos])
    {
        node->children[pos] = Create(data);

        return NULL != node->children[pos];
    }

    return InsertRec(node->children[pos], data);
}

/******************* MAIN *****************/

int main(void)
{

    Test2();
    Test3();
    Test4();
    Test5();
    Test7();
    Test8();
    Test9();
    Test13();
    Test13b();

    

    return 0;
}

void Test2()
{
    unsigned int arr[10] = {3, 5, 7, 10};

    HEADER(SumOfTwo);

    TEST(1 == IsSumOfTwo(arr, 10, 4), SumOfTwo);
    TEST(1 == IsSumOfTwo(arr, 12, 4), SumOfTwo);
    TEST(0 == IsSumOfTwo(arr, 2, 4), SumOfTwo);

}

void Test3()
{
    char arr[10] = {'a', 'b', 'c', 'd'};

    HEADER(IsFound);

    TEST(1 == Find(arr, 4, 'd'), IsFound);
    TEST(0 == Find(arr, 4, 'f'), IsFound);
}

void Test4()
{
    char arr[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    Rotate(arr, 2, 8);

    HEADER(Rotate);

    TEST('g' == arr[0], Rotate);
    TEST('f' == arr[7], Rotate);

}

void Test5()
{
    int arr[8][5] = {{1, 0, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                    {0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 0},
                    {0, 1, 0, 0, 0},
                    {1, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0},
                    {0, 0, 1, 0, 0}};

    printf("\nNum of islands = %d \n", NumOfIslands(arr, 8, 5));
}

void Test7()
{
    char str[30] = "(5 + 3 []) * 8 <>";
    char str2[30] = "(5 + 3 []) * 8 >";

    HEADER(IsParBalanced);

    TEST(1 == CheckParaneth(str), IsParBalanced);
    TEST(0 == CheckParaneth(str2), IsParBalanced);
}

void Test8()
{
    HEADER(MulRec);

    TEST(6 == MulRec(2,3), MulRec);
    TEST(20 == MulRec(4,5), MulRec);

    HEADER(IncerementRec);

    TEST(3 == IncerementRec(2), IncerementRec);
    TEST(1 == IncerementRec(0), IncerementRec);
}

void Test9()
{
    int pivot = 4;

    dll_t *dll = NULL;

    node_t *head = NULL;
    node_t *tail = NULL;
    node_t *node1 = NULL;
    node_t *node2 = NULL;
    node_t *node3 = NULL;
    node_t *node4 = NULL;
    node_t *pivot_node = NULL;

    int *data1 = NULL;
    int *data2 = NULL;
    int *data3 = NULL;
    int *data4 = NULL;
    int *data_pivot = NULL;

    data1 = malloc(sizeof(int));
    *data1 = 5;
    node1 = malloc(sizeof(node_t));
    node1->data = data1;
    node1->next = NULL;
    head = node1;
    tail = node1;

    data2 = malloc(sizeof(int));
    *data2 = 2;
    node2 = malloc(sizeof(node_t));
    node2->data = data2;
    node2->next = NULL;
    tail->next = node2;
    tail = node2;

    data3 = malloc(sizeof(int));
    *data3 = 8;
    node3 = malloc(sizeof(node_t));
    node3->data = data3;
    node3->next = NULL;
    tail->next = node3;
    tail = node3;

    data4 = malloc(sizeof(int));
    *data4 = 3;
    node4 = malloc(sizeof(node_t));
    node4->data = data4;
    node4->next = NULL;
    tail->next = node4;
    tail = node4;

    dll = malloc(sizeof(dll_t));
    dll->head = head;
    dll->tail = tail;

    data_pivot = malloc(sizeof(int));
    *data_pivot = pivot;
    pivot_node = malloc(sizeof(node_t));
    pivot_node->data = data_pivot;
    pivot_node->next = NULL;
    pivot_node->prev = NULL;

    HEADER(PivodDLL);

    printf("Initial list: ");
    PrintList(head);

    /*PivodDLL(head, pivot);*/
    SortDLL(dll, pivot_node);

    printf("Modified list: ");
    PrintList(head);

    free(data1);
    free(node1); 

    free(data2);
    free(node2); 

    free(data3);
    free(node3); 

    free(data4);
    free(node4); 
}

void Test13()
{
    int data10 = 10;
    int data2 = 2;
    int data8 = 8;
    int data6 = 6;
    int data12 = 12;
    int data14 = 14;

    bst_node_t *node = Create(&data10);

    HEADER(InsertIter);

    InsertIter(node, &data2);
    InsertIter(node, &data8);
    InsertIter(node, &data6);
    InsertIter(node, &data14);
    InsertIter(node, &data12);

    PrintTree(node, 0);
}

void Test13b()
{
    int data10 = 10;
    int data2 = 2;
    int data8 = 8;
    int data6 = 6;
    int data12 = 12;
    int data14 = 14;

    bst_node_t *node = Create(&data10);

    HEADER(InsertRec);

    InsertRec(node, &data2);
    InsertRec(node, &data8);
    InsertRec(node, &data6);
    InsertRec(node, &data14);
    InsertRec(node, &data12);

    PrintTree(node, 0);
}
