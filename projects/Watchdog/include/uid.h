#ifndef __ILRD_OL139_40_UID_H__
#define __ILRD_OL139_40_UID_H__

#include <sys/types.h> /*pid_t, getpid, size_t*/
#include <time.h> /*time_t*/

#define LINUX_IP_SIZE (14)

typedef struct uid ilrd_uid_t;

/* UID is a struct used for attaching a unique identifier to objects. */
struct uid
{
    time_t time_stamp;
    size_t counter;
    pid_t pid;
    unsigned char ip[LINUX_IP_SIZE];
};


/*
* UIDCreate Description:
*	Creates a new UID. 
*
* @params:
*   None
*
* @returns:
*	ilrd_uid_t struct
*
* @Complexity
*	O(1)
*/
ilrd_uid_t UIDCreate(void); 

/*
* UIDIsSame Description:
*	Checks if two UIDs are the same.
*
* @params:
*   lhs, rhs - UIDs
*
* @returns:
*	1 if two UIDs are the same, 0 if not.
*
* @Complexity
*	O(1)
*/
int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs); 

/*
* UIDGetBad Description:
*	Returns a UID with invalid fields.
*   This UID is used to represent a state of error.
*
* @params:
*   None.
*
* @returns:
*	UID.
*
* @Complexity
*	O(1)
*/
ilrd_uid_t UIDGetBad(void);

#endif

