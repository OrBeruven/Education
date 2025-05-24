/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for memory mapping

*****************************/

#include <stdlib.h>
/*#include <dlfcn.h>*/
#include <stdio.h>

#define BUFFSIZE 80

static void StaticFunc(void);

int a_global = 7;
static int a_static_global = 8;

const int a_global_const = -7;
const static int a_static_global_const = -8;

int MemoryMapping(int argc, char **argv, char **envp)
{
	/*void (*name)(int);*/
	
	int a = 4;	
	const int a_const = -4;
	
	static int a_static = 5;
	const static int a_static_const = -5;
	
	char *str = NULL;
	/*void *lib_handler = NULL;*/
	
	char *literal = "String Literal";
	const char *literal_const = "Const String Literal";
	
	char env_user[BUFFSIZE] = {0};
	const char *env_const = envp[0];
	
	char *command_line = argv[0];
	const char *command_line_const = argv[1];
	
	sprintf(env_user, "%s", getenv("USER"));
	/*
	lib_handler = dlopen("./libmylib.so", RTLD_LAZY);
	
	if (NULL == lib_handler)
	{
		perror("failed to open");
	}
	
	*(void **)&name = dlsym(lib_handler, "foo");
	
	(*name)(a);*/
	
	str = (char *)malloc(sizeof(char) * BUFFSIZE);
	str = "Dynamic Heap Str";
	
	printf("\na_global = %d, %p\n", a_global, &a_global);
	printf("a_static_global = %d, %p\n", a_static_global, &a_static_global);
	printf("a_global_const = %d, %p\n", a_global_const, &a_global_const);
	printf("a_static_global_const = %d, %p\n\n", a_static_global, &a_static_global);
	
	printf("a = %d, %p\n", a, &a);
	printf("a_const = %d, %p\n\n", a_const, &a_const);

	printf("a_static = %d, %p\n", a_static, &a_static);
	printf("a_static_const = %d, %p\n\n", a_static_const, &a_static_const);
	
	printf("literal = %s, %p\n", literal, literal);
	printf("literal_const = %s, %p\n\n", literal_const, literal_const);
	
	printf("env_user = %s, %p\n", env_user, env_user);
	printf("env_const = %s, %p\n\n", env_const, env_const);
	
	printf("Dynamic heap str = %s, %p\n\n", str, str);
	
	printf("command line = %s, %p\n", command_line, command_line);
	printf("command line const = %s, %p\n", command_line_const, command_line_const);
	
	StaticFunc();
	
	/*dlclose(lib_handler);*/
	
	return 0;
}

static void StaticFunc(void)
{
	printf("Static Func %p\n", StaticFunc);
}
