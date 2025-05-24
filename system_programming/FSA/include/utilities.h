/*****************************
	Name : Or Beruven


	Description : header file for utilities

*****************************/

#ifndef UTILITIES_H
#define UTILITIES_H

/********************************************
				TEST MACRO
**********************************************/

#define RESULTSTATUS(status, expected_status) ((status) == (expected_status)) ? \
											printf("\x1b[32mSUCCESS \x1b[0m\n") :\
											printf("\x1b[31mFAILURE \x1b[0m | Line: %d\n", __LINE__)





/********************************************
				COLORS!!!
**********************************************/
#define GREEN_OUT_PUT printf("\033[0;32m");

#define RED_OUT_PUT printf("\033[0;31m");

#define NORMAL_OUT_PUT printf("\033[0m");








#endif
