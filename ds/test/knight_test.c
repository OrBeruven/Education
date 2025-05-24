/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File for  Test

*****************************/
#include <stdio.h>	    /*printf*/
#include <sys/types.h>  /*pid_t*/
#include <assert.h>	    /*assert*/

#include <wchar.h>      /*wchar_t*/
#include <locale.h>     /*setlocale()*/
#include <stdlib.h>     /*system*/
#include <unistd.h>     /*sleep*/
#include <pthread.h>    /*pthread_t*/

#include "knight.h"
#include "utilitiestwo.h"

#define SUCCESS 0
#define FAIL 1

typedef enum chrs {
    b_checker = 0x25A1,
    w_checker = 0x25A0,
    b_knight = 0x1F436,
    paw = 0x1F43E,
    tab = 0x0009
}chrs_t;

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
void PrintBoardCurr(int solution[SIZE_ROW][SIZE_COL]);
/*******************************************************************************

*******************************************************************************/
int main(void)
{
    int matrix[SIZE_ROW][SIZE_COL] = {0};
    int status = 0;
    
    (void)matrix;
    status = KnightTour(matrix, 1, 1);
  
    if (0 == status)
    {
        setlocale(LC_CTYPE, "");
        wprintf(L"%lc %lc %lc %lc\n", tab, tab, tab, tab);
        PrintBoardCurr(matrix);
    }
    else
    {
        RESULT_STATUS(0, 1, INVALID);
        printf("\nNo Valid Moves\n");
    }
    
    
    /*PrintBoard(matrix);*/
    
    return 0;
}
/*******************************************************************************
                    Test Function Implementation                            
*******************************************************************************/
void PrintBoardCurr(int solution[SIZE_ROW][SIZE_COL])
{
    size_t count = 1;
    size_t i = 0;
    size_t j = 0;

    assert(NULL != solution);
    
    setlocale(LC_CTYPE, "");

    for (count = 1; count <= (SIZE_ROW * SIZE_COL); ++count)
    {
        system("clear");
        for (i = 0; i < SIZE_ROW; ++i)
        {
            for (j = 0; j < SIZE_COL; ++j)
            {
                if (count == (size_t)solution[i][j])
                {
                    wprintf(L"%lc%lc", b_knight, tab);
                }
                else if (count > (size_t)solution[i][j])
                {
                    
                    wprintf(L"%lc%lc", paw, tab);
                }
                else
                {
                    if (i % 2 == 0)
                    {
                        if (j % 2 == 0)
                        {
                            wprintf(L"%lc%lc", w_checker, tab);
                        }
                        else
                        {
                            wprintf(L"%lc%lc", b_checker, tab);
                        }
                    }
                    else
                    {
                        if (j % 2 == 1)
                        {
                            wprintf(L"%lc%lc", w_checker, tab);
                        }
                        else
                        {
                            wprintf(L"%lc%lc", b_checker, tab);
                        }
                    }
                }
            }
            wprintf(L"%lc%lc", 0x000A, 0x000A);
        }
        sleep(1);
    }
}



/*******************************************************************************

*******************************************************************************/
