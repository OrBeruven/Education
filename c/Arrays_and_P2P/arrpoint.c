#include <stdio.h> /*using - size_t, NULL, printf, scanf(in tests), puts */
#include <stdlib.h>/* using - malloc, free */
#include <string.h>/* using - strlen */
#include <ctype.h>/* using - tolower */
#include <assert.h> /* using - assert*/

/*******************
I hidden the test calls for func
from question,
some of them didnt compile
**************************
int foo1(int arr[3][3]);

void foo2(int arr[][2], int n);

void foo3(int m, int n, int arr[][n]);

void foo4(int arr[3][3], int m, int n);
*/

/******************
questions funcitons
******************/
void MatrixSum(int arr[3][3], int result[3]);

void PrintDataType();

int JosephusProbEasy(int arr[], int size);
int JosephusProbHard(int arr[], int size);

/*	Functions for env exercise */
void CoppyStrings(char **new_env, char **envp);
size_t GetStringSize(char **envp);
void StringsToLower(char **new_env, char **envp, size_t size);
void PrintStrings(char **strings, size_t size);
void CleanUp(char **to_clean, size_t size);

/*
void foo5(int (*arr)[n]);


const int m = 3;
const int n = 3;
*/
int main(int argc, char *argv[], char *envp[])
{	
	size_t size = 0;
	char **new_env;
	
	size = GetStringSize(envp);
		
	new_env = (char **)malloc(sizeof(char *) * size);
	
	if (NULL == new_env)
	{
		printf("***\tALLOCATION PROBLEM\t***\n ***\tReturning void\t***\n");
		return 1;
	}
	
	CoppyStrings(new_env, envp);
	
	/*puts(*(new_env + 0));*/
	
	StringsToLower(new_env, envp, size);
	
	PrintStrings(new_env, size);
	
	CleanUp(new_env, size);
	
	return 0;
}


void CoppyStrings(char **new_env, char **envp)
{
	int i =0;
	
	assert(NULL != new_env);
	assert(NULL != envp);
	
	for(i = 0; 0 != *(envp + i); ++i)
	{
		*(new_env + i) = (char *)malloc(sizeof(char) * (strlen(*(envp + i)) + 1));
		
		/*	Terminate the function if error accured */
		if (NULL == *(new_env + i))
		{
			printf("***\tALLOCATION PROBLEM\t***\n ***\tReturning void\t***\n");
			return;
		}
		strcpy(*(new_env + i), *(envp + i));
	}
	
	return;
}

size_t GetStringSize(char **envp)
{
	size_t i = 0;
	
	assert(NULL != envp);
	
	for(i = 0; 0 != *(envp + i); ++i)
	{
		/*Empty on purpose */
	}
	
	return i;
}
	

void StringsToLower(char **new_env, char **envp, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != new_env);
	assert(NULL != envp);
	
	for (i = 0; i < size; ++i)
	{
		while ('\0' != *(*(envp + i) + j))
		{
			*(*(new_env + i) + j) = tolower(*(*(envp + i) + j));
			++j;
		}
		j = 0;
	}
		
	return;		
}

void PrintStrings(char **strings, size_t size)
{
	size_t i = 0;
	assert(NULL != strings);
		
	for(i = 0; i < size; ++i)
	{
		puts(*(strings + i));
	}
	
	return;
}

void CleanUp(char **to_clean, size_t size)
{
	size_t i = 0;
	assert(NULL != to_clean);
	
	for(i = 0; i < size; ++i)
	{
		free(*(to_clean + i));
	}

	free(to_clean);
	
	printf("\nAll cleaned up :)\n");
	return;
}



void MatrixSum(int arr[3][3], int result[3])
{

	int i = 0;
	int j = 0;
	int res = 0;
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; j++)
		{
			res += arr[i][j];
		}
		
		printf("The sum of row %d is %d\n", i, res);
		result[i] = res;
		res = 0;
	}
	
	return;
}

/**************
print all data types sizes
**************/
void PrintDataType()
{
	printf("Data type of unsigned char %ld\n", sizeof(unsigned char));
	printf("Data type of char %ld\n", sizeof(char));
	printf("Data type of unsigned int %ld\n", sizeof(unsigned int));
	printf("Data type of int %ld\n", sizeof(int));
	printf("Data type of unsigned short int  %ld\n", sizeof(unsigned short int));
	printf("Data type of short int %ld\n", sizeof(short int));
	printf("Data type of unsigned long int %ld\n", sizeof(unsigned long int));
	printf("Data type of long double %ld\n", sizeof(long double));
	printf("Data type of double %ld\n", sizeof(double));
	printf("Data type of float %ld\n", sizeof(float));
	
	return;
}

/* not my Algorithm, tried to implement */
int JosephusProbHard(int arr[], int size)
{
	/*counting the dead soldiers */
	int num_of_soldiers = 0;
	int sword = 0;
	int num = 1;
	
	while (num_of_soldiers < size - 1)
	{
		while (1 >= num)
		{
			++sword;
			
			sword = sword % size;
			
			if (0 == arr[sword])
			{
				++num;
			}
		}
		
		num = 1;
		
		arr[sword] = 1;
		
		++num_of_soldiers;
		++sword;
		
		sword = sword % size;
		
		while (1 == arr[sword])
		{
			++sword;
			sword = sword % size;
		}
	}
	
	return sword + 1;	
}

/*Naive answer */
int JosephusProbEasy(int arr[], int size)
{
	int num_of_soldiers = 0;
	int i = 0;
	do
	{
		/*Find next soldier alive */
		while (arr[i] != 0)
		{
			++i;
			if (i >= size-1)
			{
				i = 0;
			}
		}
		
		if (i >= size-1)
		{
			i = 0;
		}
		else
		{
			++i;
		}
		/*Find next soldier alive
		and kills him (set to 0) */
		while (arr[i] != 0)
		{
			if (i >= size-1)
			{
				i = 0;
			}
			else
			{
				++i;
			}
		}
		
		arr[i] = 1;
		++num_of_soldiers;
		
		if (num_of_soldiers >= size-1)
		{
			break;
		}
		++i;	
		
	} while(1);
	
	/* Finding the last standing soldier */
	i = 0;
	while (arr[i] != 0)
	{
		++i;
	}
	
	return i+1;	
}
		
		
		
/*
int foo1(int arr[3][3])
{
	printf("Access like this %d\n", arr[1][1]);
	printf("The size is %ld\n" ,sizeof(*arr));
	return 0;
}*/

/*
void foo2(int arr[][2], int n)
{
	printf("Access like this %d\n", arr[n-1][1]);
	printf("%d\n", sizeof(arr));
}
*/

/*
void foo3(int **arr, int m, int n)
{
	printf("Access like this %d\n", arr[n-1][m-1]);
	printf("%d\n", sizeof(arr));
}


void foo4(int arr[3][3], int m, int n)
{
	int i = 0;
	int j = 0;
	
	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			printf("%d ", arr[i][j]);
		}
	}
	
	printf("%ld\n", sizeof(*arr));
}
*/
/*
void foo5(int (*arr)[m])
{
	printf("Access like this %d\n", arr[1][1]);
	printf("%d\n", sizeof(arr));
}*/
