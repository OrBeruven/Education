#include <stdio.h>
#include <dlfcn.h>
#include <stddef.h>
#include "migv1.h"


int main(void)
{
	void *handler_lib_1 = NULL;
	void *handler_lib_2 = NULL;
	
	void (*func_ptr1)();
	void (*func_ptr2)();
	
	handler_lib_1 = dlopen("libmigv1.so", RTLD_LAZY);
	handler_lib_2 = dlopen("libmigv2.so", RTLD_LAZY);
	
	if(NULL == handler_lib_2 || NULL == handler_lib_1)
	{
		printf("failed to open librarys\n");
		return 0;
	}  
	
	*(void **)(&func_ptr1) = dlsym(handler_lib_1, "Foo");
	*(void **)(&func_ptr2) = dlsym(handler_lib_2, "Foo2");
	
	func_ptr1();
	func_ptr2();

	
	dlclose(handler_lib_1);
	dlclose(handler_lib_2);
	
	return 0;
}
