#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "ipv4netid.h"
#define IP_ADDR_SEGMENTS 4
#define BINARY_DIGITS 8
#define IP_ADDR_SEGMENTS 4
#define MAX_DIGITS_IN_IP_ADDR_SEGMENT 4
#define IP_MAX_LENGTH 15
#define REGEX_FOR_IP "^[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}$"
#define PROMPT_FOR_IP "Enter IP address: "
#define PROMPT_FOR_SUBNET "Enter subnet mask: "

char ipstring[IP_MAX_LENGTH];
char subnetstring[IP_MAX_LENGTH];
int ipbinary[IP_ADDR_SEGMENTS][BINARY_DIGITS];
int subnetbinary[IP_ADDR_SEGMENTS][BINARY_DIGITS];
int netid[IP_ADDR_SEGMENTS][BINARY_DIGITS];
char ipchars[IP_ADDR_SEGMENTS][MAX_DIGITS_IN_IP_ADDR_SEGMENT];
char subnetchars[IP_ADDR_SEGMENTS][MAX_DIGITS_IN_IP_ADDR_SEGMENT];
int ipdecimal[IP_ADDR_SEGMENTS];
int subnetdecimal[IP_ADDR_SEGMENTS];
regex_t regex;
int regexcomp;

int main(int argc, char **argv)
{
    regexcomp = regcomp(&regex, REGEX_FOR_IP, REG_EXTENDED);

    validateipinput(PROMPT_FOR_IP, ipstring, &regex, ipchars, ipdecimal);

    splitipstring(ipstring, ipchars);
    convertipstring(ipchars, ipdecimal);
    tobinary(ipdecimal, ipbinary);

    validateipinput(PROMPT_FOR_SUBNET, subnetstring, &regex, subnetchars, subnetdecimal);

    regfree(&regex);

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
