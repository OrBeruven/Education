#ifndef __ILRD__OL13940_DHCP__
#define __ILRD__OL13940_DHCP__

#define BYTES_IN_IP (4)

/*Every IP address is represented as abranch in a trie
Each node in the trie should have an 'is_full' flag; this will indicate a full subtree, rooted by that node*/

typedef struct dhcp_s dhcp_t;

typedef enum dhcp_status
{
    SUCCESS = 0,
    FULL = 1,   /*DHCP is full*/
    DOUBLE_FREE = 2, /*free already freed address*/
    DS_FAILURE = 3, /*memory allocation failure in data structure*/
    INVALID_FREE = 4 /*free network, server or broadcast addresses*/
} dhcp_status_t;

/*
* DHCPCreateDHCP description:
*	Recieves the subnet ID for the DHCP to manage the addresses with.
*   Network, Server and Broadcast adresses are to be allocated implicitly (check BrainFuel)
*
* @param:
*   subnet_ip - string containing the subnet ip of constant digits
*	bits_in_subnet - number of available bits to allocate
* 
* @return:
*   Returns - A DHCP pointer, in failure returns NULL
*
* complexity
*	Time: O(log(n)).
*	Space O(1)
*/
dhcp_t *DHCPCreateDHCP(unsigned char *subnet_ip, size_t bits_in_subnet);

/*
* DHCPAllocateIp description:
*	Allocates an ip address whici is as similar as possible to the requested ip
*   The IP should be the smallest one available, that is bigger or equal to the requested one.
*   The user has the option to not specify the preferred IP, where the requested IP is considere to be all zeroes.
*
* @param:
*   DHCP - pointer to a valid DHCP
*	requested_ip - the preffered id
*   result_ip - a pointer that will evntually point to the allocated ip
* 
* @return:
*   Returns - A DHCP status indictaing success or error which specifies the error.
*
* complexity
*	Time: O(log(n)).
*	Space O(1)
*/
dhcp_status_t DHCPAllocateIp(dhcp_t *dhcp, unsigned char *requested_ip, unsigned char *result_ip);

/*
* DHCPFreeIp description:
*	Frees an Ip address in the DHCP
*
* @param:
*   DHCP - pointer to a valid DHCP
*	ip_to_free - the ip to free
* 
* @return:
*   Returns - A DHCP status indictaing success or error which specifies the error.
*
* complexity
*	Time: O(log(n)).
*	Space O(1)
*/
dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, unsigned char *ip_to_free);

/*
* DHCPCountFree description:
*	Counts the number of free IPs in the DHCP
*
* @param:
*   DHCP - pointer to a valid DHCP
* 
* @return:
*   Returns - Number of free IPs in the DHCP
*
* complexity
*	Time: O(n).
*	Space O(1)
*/
size_t DHCPCountFree(const dhcp_t *dhcp);

/*
* DHCPDestroy description:
*	Deallocates memory for a DHCP
*
* @param:
*   DHCP - pointer to a valid DHCP
* 
* @return:
*   none
*
* complexity
*	Time: O(n).
*	Space O(1)
*/
void DHCPDestroy(dhcp_t *dhcp);

#endif