/*******************************
*    Developer : Yotam sasson  *
*    Date      : 16.04.2023    *
*    Reviewer  :            *
*******************************/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "dhcp.h"

static void DrawSuccess(void);
static void DrawFailure(void);
static void TestDHCPCreateDHCP(void);
static void TestDHCPAllocateIp(void);
static void TestDHCPFreeIp(void);
static void TestDHCPCountFree(void);

int main ()
{
    TestDHCPCreateDHCP();
    TestDHCPAllocateIp();
    TestDHCPFreeIp();
    TestDHCPCountFree();
    return 0;
}

/************************ Test Functions ************************/
static void TestDHCPCreateDHCP(void)
{
    size_t bits_in_subnet = 24;
    unsigned char subnet_ip[BYTES_IN_IP] = {192, 168, 111, 0};
    dhcp_t *dhcp = DHCPCreateDHCP(subnet_ip, bits_in_subnet);

    printf("\033[4;34mDHCPCreateDHCP:\033[0m\n");

	(NULL != dhcp) ? DrawSuccess() : DrawFailure();
	assert(NULL != dhcp);

	DHCPDestroy(dhcp);
}

static void TestDHCPAllocateIp(void)
{
    int status = 0;
    size_t bits_in_subnet = 23;
    size_t i = 0;
    unsigned char subnet_ip[BYTES_IN_IP] = {192, 168, 111, 0};
    unsigned char new_ip[BYTES_IN_IP] = {0};
    unsigned char new_ip2[BYTES_IN_IP] = {0};
    unsigned char new_ip3[BYTES_IN_IP] = {0};
    unsigned char new_ip4[BYTES_IN_IP] = {0};
    unsigned char new_ip5[BYTES_IN_IP] = {0};
    unsigned char new_ip6[BYTES_IN_IP] = {0};
    unsigned char new_ip7[BYTES_IN_IP] = {0};
    unsigned char new_ip8[BYTES_IN_IP] = {0};
    unsigned char requested_ip[BYTES_IN_IP] = {255, 255, 255, 254};
    unsigned char requested_ip2[BYTES_IN_IP] = {192, 131, 110, 1};
    unsigned char requested_ip3[BYTES_IN_IP] = {192, 131, 110, 2};
    unsigned char requested_ip4[BYTES_IN_IP] = {0};
    unsigned char requested_ip5[BYTES_IN_IP] = {192, 131, 110, 252};
    unsigned char requested_ip6[BYTES_IN_IP] = {192, 131, 110, 252};
    unsigned char requested_ip7[BYTES_IN_IP] = {192, 131, 110, 255};
    unsigned char requested_ip8[BYTES_IN_IP] = {192, 131, 110, 255};
    
    dhcp_t *dhcp = DHCPCreateDHCP(subnet_ip, bits_in_subnet);

    printf("\033[4;34mDHCPAllocateIp:\033[0m\n");

    status = DHCPAllocateIp(dhcp, requested_ip, new_ip);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip is: %d.%d.%d.%d\n", new_ip[0], new_ip[1], new_ip[2], new_ip[3]);

    status = DHCPAllocateIp(dhcp, requested_ip2, new_ip2);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip2 is: %d.%d.%d.%d\n", new_ip2[0], new_ip2[1], new_ip2[2], new_ip2[3]);

    status = DHCPAllocateIp(dhcp, requested_ip3, new_ip3);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip3 is: %d.%d.%d.%d\n", new_ip3[0], new_ip3[1], new_ip3[2], new_ip3[3]);

    status = DHCPAllocateIp(dhcp, requested_ip4, new_ip4);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip4 is: %d.%d.%d.%d\n", new_ip4[0], new_ip4[1], new_ip4[2], new_ip4[3]);

    status = DHCPAllocateIp(dhcp, requested_ip5, new_ip5);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip5 is: %d.%d.%d.%d\n", new_ip5[0], new_ip5[1], new_ip5[2], new_ip5[3]);

    status = DHCPAllocateIp(dhcp, requested_ip6, new_ip6);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip6 is: %d.%d.%d.%d\n", new_ip6[0], new_ip6[1], new_ip6[2], new_ip6[3]);

    for (i = 0; i < 249; ++i)
    {
        status = DHCPAllocateIp(dhcp, requested_ip6, new_ip6);
    }

    status = DHCPAllocateIp(dhcp, requested_ip7, new_ip7);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip7 is: %d.%d.%d.%d\n", new_ip7[0], new_ip7[1], new_ip7[2], new_ip7[3]);

    status = DHCPAllocateIp(dhcp, requested_ip8, new_ip8);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip7 is: %d.%d.%d.%d\n", new_ip8[0], new_ip8[1], new_ip8[2], new_ip8[3]);


	DHCPDestroy(dhcp);
}

static void TestDHCPFreeIp(void)
{
    int status = 0;
    size_t bits_in_subnet = 24;
    unsigned char subnet_ip[BYTES_IN_IP] = {192, 168, 111, 0};
    unsigned char new_ip[BYTES_IN_IP] = {0};
    unsigned char new_ip2[BYTES_IN_IP] = {0};
    unsigned char new_ip3[BYTES_IN_IP] = {0};
    unsigned char new_ip4[BYTES_IN_IP] = {0};
    unsigned char requested_ip[BYTES_IN_IP] = {192, 168, 111, 1};
    unsigned char requested_ip2[BYTES_IN_IP] = {192, 168, 111, 2};
    unsigned char requested_ip3[BYTES_IN_IP] = {192, 168, 111, 254};
    unsigned char requested_ip4[BYTES_IN_IP] = {192, 168, 111, 19};
    unsigned char requested_ip5[BYTES_IN_IP] = {178, 132, 211, 20};
    dhcp_t *dhcp = DHCPCreateDHCP(subnet_ip, bits_in_subnet);

    DHCPAllocateIp(dhcp, requested_ip, new_ip);
    DHCPAllocateIp(dhcp, requested_ip2, new_ip2);

    printf("\033[4;34mDHCPFreeIp:\033[0m\n");

    status = DHCPFreeIp(dhcp, new_ip2);
    (SUCCESS == status) ? DrawSuccess() : DrawFailure();
    assert(SUCCESS == status);

    DHCPAllocateIp(dhcp, requested_ip2, new_ip3);
    printf("The new ip3 is: %d.%d.%d.%d\n", new_ip3[0], new_ip3[1], new_ip3[2], new_ip3[3]);

    status = DHCPFreeIp(dhcp, requested_ip3);
    (INVALID_FREE == status) ? DrawSuccess() : DrawFailure();
    assert(INVALID_FREE == status);

    status = DHCPFreeIp(dhcp, requested_ip);
    (SUCCESS == status) ? DrawSuccess() : DrawFailure();
    assert(SUCCESS == status);

    status = DHCPAllocateIp(dhcp, requested_ip, new_ip4);
	(SUCCESS == status) ? DrawSuccess() : DrawFailure();
	assert(SUCCESS == status);
    printf("The new ip4 is: %d.%d.%d.%d\n", new_ip4[0], new_ip4[1], new_ip4[2], new_ip4[3]);

    DHCPFreeIp(dhcp, requested_ip);
    status = DHCPFreeIp(dhcp, requested_ip);
	(DOUBLE_FREE == status) ? DrawSuccess() : DrawFailure();
	assert(DOUBLE_FREE == status);

    DHCPFreeIp(dhcp, requested_ip4);
	(DOUBLE_FREE == status) ? DrawSuccess() : DrawFailure();
	assert(DOUBLE_FREE == status);

    status = DHCPFreeIp(dhcp, requested_ip5);
    (INVALID_FREE == status) ? DrawSuccess() : DrawFailure();
    assert(INVALID_FREE == status);

	DHCPDestroy(dhcp);
}

static void TestDHCPCountFree(void)
{
    size_t count_free_ips = 0;
    size_t bits_in_subnet = 24;
    unsigned char subnet_ip[BYTES_IN_IP] = {192, 168, 111, 0};
    unsigned char new_ip[BYTES_IN_IP] = {0};
    unsigned char requested_ip[BYTES_IN_IP] = {192, 168, 111, 1};
    unsigned char requested_ip2[BYTES_IN_IP] = {192, 168, 111, 2};
    unsigned char requested_ip3[BYTES_IN_IP] = {192, 168, 111, 255};
    dhcp_t *dhcp = DHCPCreateDHCP(subnet_ip, bits_in_subnet);

    DHCPAllocateIp(dhcp, requested_ip, new_ip);
    DHCPAllocateIp(dhcp, requested_ip2, new_ip);
    DHCPAllocateIp(dhcp, requested_ip3, new_ip);

    printf("\033[4;34mDHCPCountFree:\033[0m\n");
    count_free_ips = DHCPCountFree(dhcp);
    (250 == count_free_ips) ? DrawSuccess() : DrawFailure();
    assert(250 == count_free_ips);

    DHCPFreeIp(dhcp, requested_ip2);
    count_free_ips = DHCPCountFree(dhcp);
    (251 == count_free_ips) ? DrawSuccess() : DrawFailure();
    assert(251 == count_free_ips);

    DHCPDestroy(dhcp);
}

/************************Print Functions ************************/
static void DrawSuccess(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;42mSUCCESS\033[0m\n\n");
}

static void DrawFailure(void)
{
    printf("\n\033[4;33mResult:\033[0m \033[5;41mFailed, You should be ashamed of yourself!\033[0m\n\n");
}
