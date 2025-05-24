#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/*******************************************************************************
Color Macro
*******************************************************************************/

#define GREEN_OUTPUT printf("\033[0;32m");

#define RED_OUTPUT printf("\033[0;31m");

#define NORMAL_OUTPUT printf("\033[0m");

#define PURPLE_OUTPUT printf("\033[0;35m");

#define CYAN_OUTPUT printf("\033[0;36m");

#define TEST_END CYAN_OUTPUT	printf("\nTesting is finished\n\n");	NORMAL_OUTPUT

/*******************************************************************************
Test Macro
*******************************************************************************/

#define RESULT_STATUS(status, expected_status, func_name) if((status) == (expected_status)) \
									{	printf("%-30s\t \033[0;32m SUCCESS\n\033[0m", #func_name);	 }\
									else {	printf("%-30s\t \033[0;31m FAILURE | Line: %d\n\033[0m", #func_name, __LINE__); }
									
									
#define HEADER(func_name) (printf("\t \033[0;35m %-30s\n\033[0m", #func_name));

#endif
