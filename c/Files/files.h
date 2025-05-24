/**********************

	Coded by - Or Beruven
	
	Reviewd By - 
	
	Date: 
	
	Description: header file for functions files.c
	
**************************/

#ifndef FILES_H
#define FILES_H

/*ex1 functions */
void Print(int to_print);
void test_ex1();

/*enum for phase 3 
	return 0 for success
	return 1 for error*/
enum flag {SUCCESS, ERROR};

typedef void (*foo)(int);
typedef int(*chain_func)(const char *, const char*);
typedef enum flag(*enum_chain_func)(const char *, const char *);

typedef struct print_me
{
	int num;
	foo func;
} print_me; /*without this would have compile warning - useless storage */

typedef struct chain
{
	char str[10];
	enum_chain_func action_func;
	chain_func cmp_func;
	
} chain;



/*declerations for phase1 functions*/
void PlayWithFile(char *name_of_file);

/*declerations for phase2 functions*/
void Ex2Main(char *name_of_file);
int CompareFunc(const char *str1, const char *str2);
int CompareFuncForChar(const char *str1, const char *str2);
int CompareTrue(const char *str1, const char *str2);/*for default*/
/*operating functions */
enum flag RemoveFile(const char *file_to_del, const char *dummy);/*-exit*/
enum flag CountLines(const char *file_name, const char *dummy);/*-count*/
enum flag ExitProgram(const char *dummy1, const char *dummy2);/*-exit*/
enum flag PreAppend(const char *file_name, const char *input);/* < */
enum flag DefaultAction(const char *dummy1, const char *dummy2);/* default */

#endif
