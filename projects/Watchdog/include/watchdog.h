#ifndef __ILRD_139_40__WD_H__
#define __ILRD_139_40__WD_H__

#include <stddef.h>

/* 
* MakeMeImmortal description:
*    Creates a new Watch Dog. 
*   Upon crash - The watch dog restarts the user's process.
*
* @param:
*   argc, argv -The name of the calling process file and it's arguments. 
*
* @return:
*    Returns SUCCESS (0) if the function create a watch dog.
*
* complexity
*    Time: O(?)
*    Space O(?)
*/
int MakeMeImmortal(size_t threshold ,int argc ,char *argv[]);    


/*
* DoNotResuscitate description:
*    Terminates the Watch dog in an orderly way.
*
* @param:
*
* @return:
*    Returns SUCCESS (0) if the function terminate the watch dog.
*
* complexity
*    Time: O(1)
*    Space O(1)
*/
int DoNotResuscitate();


#endif