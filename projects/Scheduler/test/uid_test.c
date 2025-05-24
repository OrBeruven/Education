/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for UID tests

*****************************/

#include <stdio.h>

#include "../include/uid.h"
#include "../include/utilities.h"

/*******************************************************************************
						Test function declarations
*******************************************************************************/
static void CreateTest(void);

static void IsSameTest(void);

static void GetBadTest(void);

/*******************************************************************************
*******************************************************************************/
int main()
{
	printf("Testing Create\n");
	CreateTest();
	printf("\n");
	
	printf("Testing IsSame\n");
	IsSameTest();
	printf("\n");
		
	printf("Testing GetBad\n");
	GetBadTest();
	printf("\n");
	
	return 0;
}

static void CreateTest(void)
{
	ilrd_uid_t temp1 = UIDCreate();
	ilrd_uid_t temp2;
	ilrd_uid_t temp3;
	ilrd_uid_t bad = UIDGetBad();
	
	RESULTSTATUS(UIDIsSame(temp1, temp2), 0);
	RESULTSTATUS(UIDIsSame(bad, temp2), 0);
	RESULTSTATUS(UIDIsSame(temp3, temp2), 0);
	
}

static void IsSameTest(void)
{	
	ilrd_uid_t temp1 = UIDCreate();
	ilrd_uid_t temp2 = UIDCreate();
		
	RESULTSTATUS(UIDIsSame(temp1, temp2), 0);
	RESULTSTATUS(UIDIsSame(temp2, temp2), 1);
	RESULTSTATUS(UIDIsSame(temp1, temp1), 1);
	RESULTSTATUS(UIDIsSame(temp2, temp1), 0);
}
	
static void GetBadTest(void)
{
	ilrd_uid_t temp1 = UIDCreate();
	ilrd_uid_t temp2 = UIDCreate();
	ilrd_uid_t bad = UIDGetBad();
	
	RESULTSTATUS(UIDIsSame(bad, temp2), 0);
	RESULTSTATUS(UIDIsSame(temp2, bad), 0);
	RESULTSTATUS(UIDIsSame(bad, temp1), 0);
	RESULTSTATUS(UIDIsSame(bad, bad), 1);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
