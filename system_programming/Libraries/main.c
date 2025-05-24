/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

/*#include <dlfcn.h>*/

int main(int argc, char **argv, char **envp)
{
	/*void *handler = 0;
	int (*func)(int, char**, char**);
	
	handler = dlopen("./libmem_map.so", RTLD_LAZY);
	
	if (!handler) 
    {
        perror("Failed to open");
        return 1;
    }
	
	*(void **)&func = dlsym(handler, "MemoryMapping");
	
	(*func)(argc, argv, envp);
	
	dlclose(handler);*/
	
	MemoryMapping(argc, argv, envp);
	
	
	return 0;
}

int printsomething(void)
{
	printf("YAY");
	return 0;
}
