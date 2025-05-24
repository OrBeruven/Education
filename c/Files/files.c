/**********************

	Coded by - Or Beruven
	
	Reviewd By - Lihi Cohen
	
	Date: 14.01.2023
	
	Description: functions implementation
	
**************************/

#include <stdio.h>/*using - size_t, NULL, printf*/
#include <stdlib.h>/* using - malloc, free */
#include <string.h> /*using - strcmp, strcpy, strlen*/
#include <assert.h> /*using - assert*/

#include "files.h"

#define SIZE 5

void Print(int to_print)
{
	printf("print from function : %d\n", to_print);
	return;
}

void test_ex1()
{
	int i =0;
	struct print_me print_arr[10];
	
	for (i = 0; 10 > i; ++i)
	{
		print_arr[i].num = i;
		print_arr[i].func = Print;
	}
	
	for (i = 0; 10 > i; ++i)
	{
		print_arr[i].func(print_arr[i].num); 
	}
	
	return;
}

void PlayWithFile(char *name_of_file)
{
	size_t check_for_error = 0;
	char buffer[100] = "";
	char *exit_value = "exit\n";
	int is_equal = 1;
	
	FILE *file_pointer;
	printf("%s\n\n", name_of_file);
	
	
	
	while (is_equal)
	{
		file_pointer = fopen(name_of_file, "a");
		/*check for errors in opening*/
		if (NULL == file_pointer)
		{
			printf("Something went wrong in opening\n");
			exit(1);
		}
		else
		{
			printf("file opened successfully\n");
		}
		
		printf("Enter a line to insert to file \nPress \"exit\" to escape : ");
		
		fgets(buffer, 100, stdin);
		
		is_equal = strcmp(buffer, exit_value);
		
		check_for_error = fwrite(buffer, 1, strlen(buffer), file_pointer);
		/*check for errors in writing*/
		if (check_for_error != strlen(buffer))
		{
			printf("Someting went wrong in writing\n");
		}
		
		if (fclose(file_pointer) == EOF)
		{
			printf("Someting went wrong with closing\n");
			exit(1);
		}
		else
		{
			printf("file closed successfully\n\n");
		}
		printf("value of buffer : %s exit_value : %s and %d\n", buffer, exit_value, is_equal);
	}
	
	return;
}

void Ex2Main(char *name_of_file)
{
	int i = 0;
	char buffer[100] = "";
	char *exit_value = "exit\n";
	int is_equal = 1;
	
	chain chains[SIZE];
	
	printf("Enter special mode (-exit to escape) : ");
	fgets(buffer, 100, stdin);
	is_equal = strcmp(buffer, exit_value);
		 
	/*fgets accepts new line escaoe character as character.
	therefore the str will be compared with \n */
	strcpy(chains[0].str, "-remove\n");
	chains[0].cmp_func = CompareFunc;
	chains[0].action_func = RemoveFile;
	
	strcpy(chains[1].str, "-count\n");
	chains[1].cmp_func = CompareFunc;
	chains[1].action_func = CountLines;
	
	strcpy(chains[2].str, "-exit\n");
	chains[2].cmp_func = CompareFunc;
	chains[2].action_func = ExitProgram;
	
	strcpy(chains[3].str, "<");
	chains[3].cmp_func = CompareFuncForChar;
	chains[3].action_func = PreAppend;
	
	/*default case */
	strcpy(chains[4].str, buffer);
	chains[4].cmp_func = CompareTrue;
	chains[4].action_func = DefaultAction;
	
	
	while (is_equal)
	{	
		for (i = 0; SIZE > i; ++i)
		{
			if (chains[i].cmp_func(chains[i].str, buffer))
			{
				if (ERROR == chains[i].action_func(name_of_file, buffer))
				{
					printf("Returned ERROR - terminating program\n");
					exit(ERROR);
				}
				break;
			}
		}
		printf("Enter special mode (-exit to escape) : ");
		fgets(buffer, 100, stdin);
		is_equal = strcmp(buffer, exit_value);		
	}
	return;
}


/* compare function for cases :
	-remove, -count, -exit and default */
int CompareFunc(const char *str1, const char *str2)
{
	return !(strcmp(str1, str2));		
}
/*compare function for < case */
int CompareFuncForChar(const char *str1, const char *str2)
{
	return !(strncmp(str1, str2, 1));
}

/*compare function for default, if reached it, always true*/
int CompareTrue(const char *str1, const char *str2)
{
	return 1;
}
	
/*action function for -remove */
enum flag RemoveFile(const char *file_to_del, const char *dummy)
{
	if(remove(file_to_del))
	{
		printf("Can't delete file %s\n", file_to_del);
		
		return ERROR;	
	}
	
	return SUCCESS;
}

/*action function for -count*/
enum flag CountLines(const char *file_name, const char *dummy)
{
	size_t count = 0;
	char ch = 0; /*store current character from string */
	
	FILE *fp;
	
	assert(NULL != file_name);
	
	fp = fopen(file_name, "r");
	/*check for opening errors */
	if (NULL == fp)
	{
		printf("Something went wrong in opening\n");
		return ERROR;
	}
	
	for (ch = getc(fp); EOF != ch; ch = getc(fp))
	{
		if ('\n' == ch)
		{
			++count;
		}
	}
	
	if (fclose(fp) == EOF)
	{
		printf("Someting went wrong with closing\n");
		return ERROR;
	}
	
	/*printing answer - phase 3 requests action
	function to return enum - SUCCESS or ERROR*/
	printf("The number of lines in %s is : %lu\n", file_name, count);
	return SUCCESS;
}

/*action function for -exit */
enum flag ExitProgram(const char *dummy1, const char *dummy2)
{
	exit(0);
	return SUCCESS;
}

/*action function for < */
enum flag PreAppend(const char *file_name, const char *input)
{
	size_t i = 1; 
	FILE *fp = NULL;
	char *file_str = NULL;
	size_t new_file_length = 0;
	size_t file_length = 0;
	size_t input_length = 0; 
	
	input_length = strlen(input) - 2;
	
	assert(NULL != file_name);
	assert(NULL != input);
	
	
	fp = fopen(file_name, "r+");
	/*check for opening errors */
	if (NULL == fp)
	{
		printf("Something went wrong in opening\n");
		return ERROR;
	}
	
	while (EOF != fgetc(fp))
	{
		++file_length;
	}
	
	new_file_length = file_length + input_length + 1 ;
	
	/*debug*/
	printf("The file length + input length = %lu + %lu = %lu\n", file_length, input_length, new_file_length);
	
	file_str = (char *) malloc((new_file_length * sizeof(char)) + 1); /*adds one - adding \n later*/
	/*check for allocating error */
	if (NULL == file_str)
	{
		printf("Something went wrong in allocation while writing");
		return ERROR;
	}
	
	for (i = 1; i < input_length + 1; ++i)
	{
		/*skip the first index ('<') */
		file_str[i-1] = input[i];
	}
	/*now i have the input string 
		next i will add the file string*/
	/*set indicator to the start of file */
	rewind(fp);
	file_str[i - 1] = '\n'; 
	for (; i <= new_file_length; ++i)
	{
		file_str[i] = fgetc(fp);
	}
	
	/*set indicator to the start of file */
	rewind(fp);
	
	for (i = 0; i < new_file_length; ++i)
	{
		if(EOF == fputc(file_str[i], fp))
		{
			printf("Something went wrong with writing, terminating mid run\n");
			return ERROR;
		}
	}
		

	if (EOF == fclose(fp))
	{
		printf("Someting went wrong with closing\n");
		return ERROR;
	}
	
	free(file_str);
	return SUCCESS;
}

enum flag DefaultAction(const char *dummy1, const char *input)
{
	printf("Ivalid input, \n%sis undefined.\n", input);
	return SUCCESS;
}
	







