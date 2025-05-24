/**********************

	Coded by - Or Beruven
	
	Reviewd By - Lihi Cohen
	
	Date: 14.01.2023
	
	Description: test file for functions files.c - sends to the right function
	
**************************/

#include <stdio.h>

/*local lib*/
#include "files.h"

void ex1();
void ex2_phase1(int argc, char *argv[]);
void ex2_phase2_test(int argc, char *argv[]);

/*the name of the file will be in argv[1] */
/* 1st argument that the user inserts other than ./a.out*/
int main(int argc, char *argv[])
{
	ex2_phase2_test(argc, argv);
	return 0;
}

void ex1()
{
	/*sending to file.c*/
	test_ex1();
}

void ex2_phase1(int argc, char *argv[])
{
	PlayWithFile(argv[1]);
}
void ex2_phase2_test(int argc, char *argv[])
{
	Ex2Main(argv[1]);
	
	return;
}
