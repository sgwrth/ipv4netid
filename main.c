#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
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
    regex_t regex;
    int regexcheck = regcomp(&regex, "^[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}$", REG_EXTENDED);
    int rangecheck = -1;

    do {
        printf("Enter IP address: ");
        scanf("%s", ipstring);

        regexcheck = regexec(&regex, ipstring, 0, NULL, 0);
        if (0 == regexcheck) {
            splitipstring(ipstring, ipchars);
            convertipstring(ipchars, ipdecimal);
            for (int i = 0; i < 4; i++) {
                printf("%d ", ipdecimal[i]);
            }
            if ((0 <= ipdecimal[0] && ipdecimal[0] <= 255)
                && (0 <= ipdecimal[1] && ipdecimal[1] <= 255)
                && (0 <= ipdecimal[2] && ipdecimal[2] <= 255)
                && (0 <= ipdecimal[3] && ipdecimal[3] <= 255)) {
                rangecheck = 0;
            } else {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 3; j++) {
                        ipchars[i][j] = '\0';
                    }
                }
                for (int i = 0; i < 4; i++) {
                    ipdecimal[i] = 0;
                }
                printf("Sorry, address out of range!\n");
            }
        } else {
                printf("Sorry, wrong format!\n");
        }
    } while (rangecheck != 0);

    splitipstring(ipstring, ipchars);

    convertipstring(ipchars, ipdecimal);

    tobinary(ipdecimal, ipbinary);

    rangecheck = -1;

    do {
        printf("Enter subnet mask: ");
        scanf("%s", subnetstring);

        regexcheck = regexec(&regex, subnetstring, 0, NULL, 0);
        if (0 == regexcheck) {
            splitipstring(subnetstring, subnetchars);
            convertipstring(subnetchars, subnetdecimal);
            for (int i = 0; i < 4; i++) {
                printf("%d ", subnetdecimal[i]);
            }
            if ((0 <= subnetdecimal[0] && subnetdecimal[0] <= 255)
                && (0 <= subnetdecimal[1] && subnetdecimal[1] <= 255)
                && (0 <= subnetdecimal[2] && subnetdecimal[2] <= 255)
                && (0 <= subnetdecimal[3] && subnetdecimal[3] <= 255)) {
                rangecheck = 0;
            } else {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 3; j++) {
                        subnetchars[i][j] = '\0';
                    }
                }
                for (int i = 0; i < 4; i++) {
                    subnetdecimal[i] = 0;
                }
                printf("Sorry, address out of range!\n");
            }
        } else {
                printf("Sorry, wrong format!\n");
        }
    } while (rangecheck != 0);

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
