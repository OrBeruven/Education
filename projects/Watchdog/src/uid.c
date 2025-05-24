/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for UID Implementation

*****************************/

#include <ifaddrs.h> 	/*getifaddrs, struct ifaddrs, freeifaddrs*/
#include <string.h> 	/*memcpy, memcmp*/
#include <unistd.h> 	/*getpid*/
#include <arpa/inet.h> 	/*struct sockaddr_in*/
#include <assert.h>

#include "../include/uid.h"

/*******************************************************************************
*******************************************************************************/

#define FAILURE -1
#define SUCCESS 0
#define ISSAME 1

/*******************************************************************************
						Help function declarations
*******************************************************************************/
static int GetIP(ilrd_uid_t *new_uid);

/*******************************************************************************
*******************************************************************************/

/*0 is reserved for bad UID*/
static size_t task_counter = 1;

/*BadUID const global*/
const ilrd_uid_t bad_uid = {0};

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid = {0};
	
	new_uid.time_stamp = time(NULL);
	new_uid.counter = task_counter;
	++task_counter;
	
	new_uid.pid = getpid();
	
	if (FAILURE == GetIP(&new_uid))
	{
		return UIDGetBad();
	}
    
	return new_uid;
}

int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs)
{
	int flag = 0;
	
	if (0 == difftime(lhs.time_stamp, rhs.time_stamp))
	{
		if (lhs.counter == rhs.counter)
		{
			if (lhs.pid == rhs.pid)
			{
				if (0 == memcmp(lhs.ip, rhs.ip, LINUX_IP_SIZE))
				{
					flag = ISSAME;
				}
			}
		}
	}
	
	return flag;
}

ilrd_uid_t UIDGetBad(void)
{
	return bad_uid;
}


/*******************************************************************************
						Help function definitions
*******************************************************************************/
static int GetIP(ilrd_uid_t *new_uid)
{
	struct ifaddrs *ifap = NULL;
    struct ifaddrs *ifa_runner = NULL;
    struct sockaddr_in *sock = NULL;
    
    assert(NULL != new_uid);
    
    if (FAILURE == getifaddrs(&ifap))
	{
		return FAILURE;
	}
	
	for (ifa_runner = ifap; NULL != ifa_runner; ifa_runner = ifa_runner->ifa_next) 
    {
        if (NULL != ifa_runner->ifa_addr && AF_INET ==ifa_runner->ifa_addr->sa_family)
        {
            sock = (struct sockaddr_in *)ifa_runner->ifa_addr;
            memcpy(new_uid->ip, inet_ntoa(sock->sin_addr), LINUX_IP_SIZE);
		}
    }
	
    freeifaddrs(ifap);
    
    return SUCCESS;
}
/*******************************************************************************
*******************************************************************************/
