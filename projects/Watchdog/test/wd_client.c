/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File for  Test

*****************************/
#include <stdlib.h>
#include <unistd.h>    /*sleep*/
#include <stdio.h>	/*printf*/
#include <assert.h>	/*assert*/
#include <signal.h> /*raise*/

#include "utilitiestwo.h"
#include "watchdog.h"

#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/
void UserFunctionRun(void);

/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/

/*******************************************************************************

*******************************************************************************/
/* int main(void)
{
    if (0 != MakeMeImmortal(3, 1, NULL))
    {
        perror("ERROR");
        return 1;
    }

    UserFunctionRun();

    DoNotResuscitate();

    return 0;
} */

int main(int argc, char *argv[])
{
	size_t i = 12;

    printf("\nUser process start\n");
	if (FAIL == MakeMeImmortal(2, argc, argv))
    {
        printf("GOOD its not working\n");
    }

	for (; i != 0; --i)
	{
		printf("\nIm Still Running! %lu sec left\n", i);
		sleep(1);
	}
    /* UserFunctionRun(); */

	DoNotResuscitate();

	return 0;
}


/*******************************************************************************
                    Test Function Implementation
*******************************************************************************/
void UserFunctionRun(void)
{
    char ch = 0;
    printf("Running from the beginning\n");
    printf("Insert e to quit elegantly, c to cancel and crush : \n");

    while (('e') != ch)
	{
		ch = getchar();
		
		switch (ch)
		{
			case 67:
			case 99:
				printf("c pressed\n");
                printf("Crushing the program\n");
				raise(SIGTERM);
				
		}
	}

    return;
}

/*******************************************************************************

*******************************************************************************/