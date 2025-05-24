/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File for  implemantation

*****************************/
#include <stdlib.h>     /*qsort*/
#include <stdio.h>      /*printf*/
#include <unistd.h>     /*alarm*/
#include <assert.h>	    /*assert*/
#include <pthread.h>    /*pthread_t*/

#include "knight.h"
#include "pq_heap.h"

#define NOT_VALID 0
#define VALID 1

#define SUCCESS 0
#define FAIL 1

#define UNVISITED 0
#define NUM_OF_KNIGHT_MOVES 8

#define ALARM_TIME 1
#define ALARM_OFF 0

typedef struct knight_moves
{
    int row;
    int col;
    int num_of_moves;
} knight_moves_t;

typedef struct board
{
    int *matrix;
    int row;
    int col;
} board_t;

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
static int IsValidMove(int matrix[SIZE_ROW][SIZE_COL],int row, int col);

static int KnightTourRec(int matrix[SIZE_ROW][SIZE_COL], int row, int col);

static size_t CountValidMoves(int matrix[SIZE_ROW][SIZE_COL], int row, int col, knight_moves_t moves[NUM_OF_KNIGHT_MOVES]);

static int CompareKnightMoves(const void *lhs, const void *rhs);

static void *RunKnightTourWrap(void *arg);
/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
int KnightTour(int matrix[SIZE_ROW][SIZE_COL], int row, int col)
{
    size_t i = 0;
    size_t j = 0;

    void *thread_return_status = NULL;
    pthread_t thread;
    board_t board = {NULL, 0, 0};

    assert(NULL != matrix);

    if (!IsValidMove(matrix, row, col))
    {
        return FAIL;
    }

    board.matrix = (int *)matrix;
    board.col = col;
    board.row = row;

    for (i = 0; i < SIZE_ROW; ++i)
    {
        for (j = 0; j < SIZE_COL; ++j)
        {
            matrix[i][j] = UNVISITED;
        }
    }

    pthread_create(&thread, NULL, RunKnightTourWrap, &board);
    pthread_join(thread, &thread_return_status);
    
    return (int)(long int)thread_return_status;
}

void PrintBoard(int solution[SIZE_ROW][SIZE_COL])
{
    size_t i = 0;
    size_t j = 0;

    assert(NULL != solution);

    for (i = 0; i < SIZE_ROW; ++i)
    {
        for (j = 0; j < SIZE_COL; ++j)
        {
            printf("%3d\t", solution[i][j]);
        }
        printf("\n");
    }
}
/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
static int KnightTourRec(int matrix[SIZE_ROW][SIZE_COL], int row, int col)
{
    size_t i = 0;
    size_t num_of_valid_moves = 0;

    knight_moves_t moves[NUM_OF_KNIGHT_MOVES] = { {2, 1, 8} , {2, -1, 8}, {-2, 1, 8}, {-2, -1, 8}, {1, 2, 8}, {1, -2, 8}, {-1, 2, 8}, {-1, -2, 8}};

    if ((SIZE_ROW * SIZE_COL) == matrix[row][col])
    {
        return SUCCESS;
    }

    for (i = 0; i < NUM_OF_KNIGHT_MOVES; ++i)
    {
        if (IsValidMove(matrix, row + moves[i].row, col + moves[i].col))
        {
            moves[i].num_of_moves = CountValidMoves(matrix, row + moves[i].row, col + moves[i].col, moves);
            ++num_of_valid_moves;
        }
    }

    qsort(moves, NUM_OF_KNIGHT_MOVES, sizeof(knight_moves_t), CompareKnightMoves);

    for (i = 0; i < num_of_valid_moves; ++i)
    { 
        matrix[row + moves[i].row][col + moves[i].col] = matrix[row][col] + 1;
        if (SUCCESS == KnightTourRec(matrix, row + moves[i].row, col + moves[i].col))
        {
            return SUCCESS;
        }

        matrix[row + moves[i].row][col + moves[i].col] = UNVISITED;
    }
    
    return FAIL;
}

static int IsValidMove(int matrix[SIZE_ROW][SIZE_COL],int row, int col)
{
    if (row < SIZE_ROW && col < SIZE_COL && row >= 0 && col >= 0 && 0 == matrix[row][col])
    {
        return VALID;
    }
    else
    {
        return NOT_VALID;
    }
}

static size_t CountValidMoves(int matrix[SIZE_ROW][SIZE_COL], int row, int col, knight_moves_t moves[NUM_OF_KNIGHT_MOVES])
{
    size_t i = 0;
    size_t count = 0;

    for (i = 0; i < NUM_OF_KNIGHT_MOVES; ++i)
    {
        if (IsValidMove(matrix, row + moves[i].row, col + moves[i].col))
        {
            ++count;
        }
    }

    return count;
}

static int CompareKnightMoves(const void *lhs, const void *rhs)
{
    return (((knight_moves_t *)lhs)->num_of_moves - ((knight_moves_t *)rhs)->num_of_moves);
}

static void *RunKnightTourWrap(void *arg)
{
    board_t *board = (board_t *)arg;
    void *return_status = 0;

    assert(NULL != arg);
    
    alarm(ALARM_TIME);
    ((int (*)[SIZE_COL])board->matrix)[board->row][board->col] = 1;
    return_status = (void *)(long int)KnightTourRec((int (*)[SIZE_COL])(board->matrix), board->row, board->col);

    alarm(ALARM_OFF);
    return return_status;
}
/*******************************************************************************
*******************************************************************************/