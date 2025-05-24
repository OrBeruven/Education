/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File For DHCP Implemantation

*****************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h>	/*assert*/

#include "dhcp.h"
#include "trie.h"

#define SUCCESS (0)
#define FAIL (1)
#define INVALID_INSERT (0)

#define BITS_IN_BYTE (8)
#define BITS_IN_INT (32)

typedef enum
{
    NETWORK = 0,
    SERVER = 1,
    BROADCAST = 2,
    NUM_RESERVED_IP = 3
}reserved_ip_t;

struct dhcp_s
{
    unsigned int reserved_addresses[NUM_RESERVED_IP];
    size_t bits_in_subnet;
    trie_t *trie;
    unsigned int subnet_mask;
};

/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
static unsigned int IpToInt(unsigned char *ip_address);

static void IntToIp(unsigned int ip, unsigned char *to_ip);

static unsigned int GetSubnetMask(dhcp_t *dhcp, unsigned char *ip);

static unsigned int GetUserID(dhcp_t *dhcp, unsigned char *ip);
/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    API Function Implementation
*******************************************************************************/
dhcp_t *DHCPCreateDHCP(unsigned char *subnet_ip, size_t bits_in_subnet)
{
    dhcp_t *new_dhcp = NULL;

    assert(NULL != subnet_ip);
    assert(2 < bits_in_subnet);

    new_dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (NULL == new_dhcp)
    {
        return NULL;
    }

    new_dhcp->trie = TrieCreate(bits_in_subnet);
    if (NULL == new_dhcp->trie)
    {
        free(new_dhcp);
        return NULL;
    }

    new_dhcp->bits_in_subnet = bits_in_subnet;

    new_dhcp->reserved_addresses[NETWORK] = TrieInsertNext(new_dhcp->trie);
    if (0 != new_dhcp->reserved_addresses[NETWORK])
    {
        DHCPDestroy(new_dhcp);
        return NULL;
    }

    new_dhcp->reserved_addresses[SERVER] = (1 << (BITS_IN_INT - bits_in_subnet)) - 1;
    if (FAIL == TrieInsert(new_dhcp->trie, new_dhcp->reserved_addresses[SERVER]))
    {
        DHCPDestroy(new_dhcp);
        return NULL;
    }

    new_dhcp->reserved_addresses[BROADCAST] = (1 << (BITS_IN_INT - bits_in_subnet)) - 2;
    if (FAIL == TrieInsert(new_dhcp->trie, new_dhcp->reserved_addresses[BROADCAST]))
    {
        DHCPDestroy(new_dhcp);
        return NULL;
    }

    new_dhcp->subnet_mask = GetSubnetMask(new_dhcp, subnet_ip);

    return new_dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    TrieDestroy(dhcp->trie);
    free(dhcp);
}

dhcp_status_t DHCPAllocateIp(dhcp_t *dhcp, unsigned char *requested_ip, unsigned char *result_ip)
{
    unsigned int user_id = 0;
    unsigned int new_ip = 0;

    assert(NULL != dhcp);
    assert(NULL != requested_ip);
    assert(NULL != result_ip);

    user_id = GetUserID(dhcp, requested_ip);

    if (FAIL == TrieInsert(dhcp->trie, user_id))
    {
        user_id = TrieInsertNext(dhcp->trie);
        if (INVALID_INSERT == user_id)
        {
            return FULL;
        }
    }

    new_ip = dhcp->subnet_mask | user_id;

    IntToIp(new_ip, (unsigned char *)result_ip);
    
    return SUCCESS;
}

dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, unsigned char *ip_to_free)
{
    unsigned int user_id_to_free = 0;
    unsigned int subnet_mask_to_free = 0;
    size_t i = 0;

    assert(NULL != dhcp);
    assert(NULL != ip_to_free);

    user_id_to_free = GetUserID(dhcp, ip_to_free);

    for (i = 0; i < NUM_RESERVED_IP; ++i)
    {
        if (user_id_to_free == dhcp->reserved_addresses[i])
        {
            return INVALID_FREE;
        }
    }

    subnet_mask_to_free = GetSubnetMask(dhcp, ip_to_free);

    if (subnet_mask_to_free != dhcp->subnet_mask)
    {
        return INVALID_FREE;
    }

    if (1 == TrieSearch(dhcp->trie, user_id_to_free))
    {
        return DOUBLE_FREE;
    }

    TrieRemove(dhcp->trie, user_id_to_free);
    return SUCCESS;
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    return (1 << (BITS_IN_INT - dhcp->bits_in_subnet)) - TrieCount(dhcp->trie);
}
/*******************************************************************************

*******************************************************************************/

/*******************************************************************************
                    Help Function Implementation
*******************************************************************************/
static unsigned int IpToInt(unsigned char *ip_address)
{
    unsigned int result = 0;
    unsigned char *p = ip_address;
    size_t i = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        result <<= 8;
        result |= *p;
        ++p;
    }

    return result;
}

static void IntToIp(unsigned int ip, unsigned char *to_ip)
{
    size_t i = 0;

    for (i = BYTES_IN_IP; i > 0; --i)
    {
        to_ip[i - 1] = (char)ip;
        ip >>= 8;
    }
}

static unsigned int GetSubnetMask(dhcp_t *dhcp, unsigned char *ip)
{
    unsigned int subnet_mask = IpToInt(ip);
    subnet_mask >>= BITS_IN_INT - dhcp->bits_in_subnet;
    subnet_mask <<= BITS_IN_INT - dhcp->bits_in_subnet;

    return subnet_mask;
}

static unsigned int GetUserID(dhcp_t *dhcp, unsigned char *ip)
{
    unsigned int user_id = IpToInt(ip);
    user_id <<= dhcp->bits_in_subnet;
    user_id >>= dhcp->bits_in_subnet;

    return user_id;
}
/*******************************************************************************

*******************************************************************************/
