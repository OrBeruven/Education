/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File for  Test

*****************************/
#include <stdio.h>	/*printf*/
#include <assert.h>	/*assert*/

#define SUCCESS 0
#define FAIL 1

#define ASCII 256
#define STR_SIZE 32

/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/
int IsSamePattern(char *st1, char *st2);

/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/


/*******************************************************************************

*******************************************************************************/
int main(void)
{
    char st1_1[STR_SIZE] = "dad";
    char st1_2[STR_SIZE] = "mom";

    char st2_1[STR_SIZE] = "acc";
    char st2_2[STR_SIZE] = "bbd";

    char st3_1[STR_SIZE] = "abcd";
    char st3_2[STR_SIZE] = "efgh";

    char st4_1[STR_SIZE] = "abab";
    char st4_2[STR_SIZE] = "cdcd";

    if (SUCCESS == IsSamePattern(st1_1, st1_2))
    {
        printf("SUCCESS\n");
    }

    if (SUCCESS != IsSamePattern(st2_1, st2_2))
    {
        printf("SUCCESS\n");
    }

    if (SUCCESS == IsSamePattern(st3_1, st3_2))
    {
        printf("SUCCESS\n");
    }
    
    if (SUCCESS == IsSamePattern(st4_1, st4_2))
    {
        printf("SUCCESS\n");
    }

    return 0;
}

/*******************************************************************************
                    Test Function Implementation
*******************************************************************************/
int IsSamePattern(char *st1, char *st2)
{
    int lut1[ASCII] = {0};
    int lut2[ASCII] = {0};
    size_t counter = 1;

    while (*st1 != '\0')
    {
        if (0 == lut1[(int)*st1] && 0 == lut2[(int)*st2])
        {
            lut1[(int)*st1] = counter;
            lut2[(int)*st2] = counter;
            ++counter;
        }
        else
        {
            if (lut1[(int)*st1] != lut2[(int)*st2])
            {
                return FAIL;
            }
        }

        ++st1;
        ++st2;
    }

    return SUCCESS;
}

/*******************************************************************************

*******************************************************************************/