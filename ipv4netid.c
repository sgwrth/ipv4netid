#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "ipv4netid.h"
#define BINARY_DIGITS 8
#define IP_ADDR_SEGMENTS 4
#define MAX_DIGITS_IN_IP_ADDR_SEGMENT 4
#define IP_MAX_LENGTH 15
#define ERROR_ADDR_OUT_OF_RANGE "Sorry, address out of range!\n"
#define ERROR_ADDR_MALFORMED "Sorry, wrong format!\n"

void splitipstring(
        char input[IP_MAX_LENGTH],
        char output[IP_ADDR_SEGMENTS][MAX_DIGITS_IN_IP_ADDR_SEGMENT])
{
    int posNr = 0;
    int m = 0;
    int n = posNr;
    for (int i = 0; i <= 3; i++) {
        while ((input[n] != '.') && (input[n] != '\0')) {
            output[i][m] = input[n];
            posNr++;
            m++;
            n++;
        }
        posNr++;
        n = posNr;
        m = 0;
    }
}

void convertipstring(char input[][MAX_DIGITS_IN_IP_ADDR_SEGMENT], int output[])
{
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        output[i] = atoi(input[i]);
    }
}

void tobinary(int input[], int output[][BINARY_DIGITS])
{
    int temp;
    for (int i = 0; i < BINARY_DIGITS; i++) {
        for (int k = 0, j = 0; k < BINARY_DIGITS; k++) {
            temp = input[i] % 2;
            input[i] = input[i] / 2;
            if(temp != 0) {
                output[i][j] = 1;
            } else {
                output[i][j] = 0;
            }
            j++;
        }
    }
}

void setnetid(
        int ip[][BINARY_DIGITS],
        int subnet[][BINARY_DIGITS],
        int netid[][BINARY_DIGITS])
{
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        for (int k = 0, j = (BINARY_DIGITS - 1); k < BINARY_DIGITS; k++, j--) {
            if ((ip[i][j] == 1) && (subnet[i][j] == 1)) {
                netid[i][j] = 1;
            } else {
                netid[i][j] = 0;
            }
        }
    }
}

void todecimal(int input[BINARY_DIGITS])
{
    int factor = 1;
    int temp[BINARY_DIGITS];
    for (int i = 0; i < BINARY_DIGITS; i++) {
        temp[i] = input[i] * factor;
        factor = factor * 2;
    }
    int result = 0;
    for (int i = (BINARY_DIGITS - 1); i >= 0; i--) {
        result = result + temp[i];
    }
    printf("%d", result);
}

void printbinaryaddress(int binary[][BINARY_DIGITS])
{
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        for (int j = (BINARY_DIGITS - 1); j >= 0; j--) {
            printf("%d", binary[i][j]);
        }
        printf(" ");
    }
}

void resetarrays(char chars[][MAX_DIGITS_IN_IP_ADDR_SEGMENT], int decimal[])
{
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        for (int j = 0; j < MAX_DIGITS_IN_IP_ADDR_SEGMENT; j++) {
            chars[i][j] = '\0';
        }
    }
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        decimal[i] = 0;
    }
}

void validateipinput(
        char *prompttext,
        char *ipstring,
        regex_t *regex,
        char ipchars[IP_ADDR_SEGMENTS][MAX_DIGITS_IN_IP_ADDR_SEGMENT],
        int ipdecimal[IP_ADDR_SEGMENTS])
{
    while (1) {
        printf(prompttext);
        scanf("%s", ipstring);
        if (0 == regexec(regex, ipstring, 0, NULL, 0)) {
            splitipstring(ipstring, ipchars);
            convertipstring(ipchars, ipdecimal);
            if (0 == iswithinrange(ipdecimal)) {
                break;
            } else {
                resetarrays(ipchars, ipdecimal);
                printf(ERROR_ADDR_OUT_OF_RANGE);
            }
        } else {
                printf(ERROR_ADDR_MALFORMED);
        }
    }
}

int iswithinrange(int ip[])
{
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        if (0 > ip[i] || ip[i] > 255) {
           return -1;
        }
    }
    return 0;
}
