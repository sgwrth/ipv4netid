#include <stdio.h>
#include <stdlib.h>
#include "ipv4netid.h"
#define IP_ADDR_SEGMENTS 4
#define BINARY_DIGITS 8
#define IP_ADDR_SEGMENTS 4
#define MAX_DIGITS_IN_IP_ADDR_SEGMENT 4
#define IP_MAX_LENGTH 15

char ipstring[IP_MAX_LENGTH];
char subnetstring[IP_MAX_LENGTH];
int ipbinary[IP_ADDR_SEGMENTS][BINARY_DIGITS];
int subnetbinary[IP_ADDR_SEGMENTS][BINARY_DIGITS];
int netid[IP_ADDR_SEGMENTS][BINARY_DIGITS];
char ipchars[IP_ADDR_SEGMENTS][MAX_DIGITS_IN_IP_ADDR_SEGMENT];
char subnetchars[IP_ADDR_SEGMENTS][MAX_DIGITS_IN_IP_ADDR_SEGMENT];
int ipdecimal[IP_ADDR_SEGMENTS];
int subnetdecimal[IP_ADDR_SEGMENTS];

int main(int argc, char **argv)
{
    printf("Enter IP address: ");
    scanf("%s", &ipstring);

    splitipstring(ipstring, ipchars);

    convertipstring(ipchars, ipdecimal);

    tobinary(ipdecimal, ipbinary);

    printf("Enter subnet mask: ");
    scanf("%s", &subnetstring);

    splitipstring(subnetstring, subnetchars);

    convertipstring (subnetchars, subnetdecimal);

    tobinary(subnetdecimal, subnetbinary);

    setnetid(ipbinary, subnetbinary, netid);

    printf("\n");
    printf("IP:\t\t");
    printbinaryaddress(ipbinary);

    printf("\nSubnet mask:\t");
    printbinaryaddress(subnetbinary);
    printf("\n");

    printf("\t\t-----------------------------------\n"); printf("Net ID:\t\t");
    printbinaryaddress(netid);
    printf("\n\n");

    printf("Net ID as IP address:\t");
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        todecimal(netid[i]);
        if (i < (IP_ADDR_SEGMENTS - 1)) {
            printf(".");
        }
    }
    printf("\n");
    return 0;
}
