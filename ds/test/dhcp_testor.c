/*****************************

    Name : Or Beruven

    Reviewed By : 

    Date Test: 00.00.2023

    Description : C File for  Test

*****************************/
#include <stdio.h>	/*printf*/
#include <assert.h>	/*assert*/

#include "dhcp.h"
#include "utilitiestwo.h"


#define SUCCESS 0
#define FAIL 1

/*******************************************************************************
                    Test Function Declarations
*******************************************************************************/
void CreateDestroyTest(void);

void InsertTest(void);
/*******************************************************************************

*******************************************************************************/


/*******************************************************************************
                    Help Function Declarations
*******************************************************************************/
static void PrintIP(unsigned char *ip);

/*******************************************************************************

*******************************************************************************/
int main(void)
{
    HEADER(Create Destroy Test);
    CreateDestroyTest();
    printf("\n");

    HEADER(Insert Test);
    InsertTest();
    printf("\n");
    return 0;
}

/*******************************************************************************
                    Test Function Implementation
*******************************************************************************/
void CreateDestroyTest(void)
{
    unsigned char ip[4] = {192, 168, 68, 51};
    dhcp_t *dhcp = NULL;

    RESULT_STATUS(dhcp == NULL, 1, Before Create);
    dhcp = DHCPCreateDHCP(ip, 28);
    RESULT_STATUS(dhcp != NULL, 1, Create);

    DHCPDestroy(dhcp);
}

void InsertTest(void)
{
    unsigned char ip[4] = {192, 168, 0, 0};
    unsigned char result[4] = {0, 0, 0, 0};
    unsigned char request[4] = {192, 168, 0, 5};
    unsigned char free_ip[4] = {192, 168, 0, 10};
    dhcp_t *dhcp = NULL;

    RESULT_STATUS(dhcp == NULL, 1, Before Create);
    dhcp = DHCPCreateDHCP(ip, 28);
    RESULT_STATUS(dhcp != NULL, 1, Create);
    request[3] = 0;
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    request[3] = 10;
    DHCPAllocateIp(dhcp, request, result);
    printf("Requested 10\n");
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);
    DHCPFreeIp(dhcp, free_ip);
    DHCPAllocateIp(dhcp, request, result);
    PrintIP(result);

    DHCPDestroy(dhcp);
}
/*******************************************************************************

*******************************************************************************/

static void PrintIP(unsigned char *ip)
{
    size_t i = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        printf("%d. ", ip[i]);
    }
    printf("\n");
}