/*
Name: Egor Markov
Tester:
Date Test:
*/

#include <stdio.h>
#include <stdlib.h>

int zero1; /* first global variable not defined */
int zero2; /* second global variable not defined */
int zero3 = 0; /* third global variable defined to 0  */
int global = 1; /* first global variable defined (not zero)  */
const int global1 = 2; /* third const global variable defined (not zero)  */
static int name = 3; /* first static variable defined (not zero)  */
static const int g = 4; /*  static cosnt variable defined (not zero)  */

static void goo()
{
	int a = 3;
	printf("foo and int = %d \n",a);
}

int recu(int x)
{
	int* ptr1;
	
	if( x == 0)
	{
		return 0;
	}
	ptr1 = (int*)malloc(1 * sizeof(int));
	if (ptr1 == NULL) 
	{
        	printf("Memory not allocated.\n");
   	}
   	printf("malloc adress %p in %d recurse \n",(void *)ptr1, x);
        printf("local x %p in %d recurse \n \n", (void *)&x, x);
	return recu(x-1);
}

int main(int argc, char *argv[], char * envp[])
{
	int local = 2;
	static int c = 5;
	static const int c1 = 6;
	char *env = envp[0];
	char *s = "string literal";

   	printf("static int adress %p  \n", (void *)&c);
   	printf("const int adress %p  \n", (void *)&c1);
   	printf("global int adress %p  \n", (void *)&global);
   	printf("const int adress %p  \n", (void *)&global1);
   	printf("static int out scope adress %p  \n", (void *)&name);
   	printf("static const int out scope adress %p  \n", (void *)&g);
   	printf("globa1 without value %p  \n", (void *)&zero1);
   	printf("globa2 without value %p  \n", (void *)&zero2);
   	printf("globa2 whit value zero %p  \n", (void *)&zero3);
   	printf("string literla %p  \n", (void *)s);
   	printf("local %p  \n", (void *)&local);
   	printf("goo func adress %p  \n", goo);
   	printf("environment variable adress %p  \n", (void *)env);
   	
   	printf("\n________recu function prints________ \n \n");
	recu(5);
	return 0;
}

