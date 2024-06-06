#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "ipv4netid.h"
#define BINARY_DIGITS 8
#define IP_ADDR_SEGMENTS 4
#define MAX_DIGITS_IN_IP_ADDR_SEGMENT 3
#define IP_MAX_LENGTH 15
#define REGEX_FOR_IP "^[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}$"
#define ERROR_ADDR_OUT_OF_RANGE "Sorry, address out of range!\n"
#define ERROR_ADDR_MALFORMED "Sorry, wrong format!\n"

int initregex(regex_t *regex) {
    return regcomp(regex, REGEX_FOR_IP, REG_EXTENDED);
}

char **splitup(char *input)
{
    char *values = (char*)malloc(MAX_DIGITS_IN_IP_ADDR_SEGMENT * sizeof(char));
    char **output = (char**)malloc(IP_ADDR_SEGMENTS * sizeof(values));
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        output[i] = malloc(MAX_DIGITS_IN_IP_ADDR_SEGMENT * sizeof(char));
    }
    int posNr = 0;
    int m = 0;
    int n = posNr;
    for (int i = 0; i <= MAX_DIGITS_IN_IP_ADDR_SEGMENT; i++) {
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
    return output;
}

int *todecimal(char **input)
{
    int *output = (int*)malloc(IP_ADDR_SEGMENTS * sizeof(int));
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        output[i] = atoi(input[i]);
    }
    return output;
}

int **tobinary(int *input)
{
    int *octet = (int*)malloc(BINARY_DIGITS * sizeof(int));
    int **output = (int**)malloc(IP_ADDR_SEGMENTS * sizeof(octet));
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        output[i] = malloc(BINARY_DIGITS * sizeof(int));
    }
    int temp;
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        for (int k = 0, j = 0; k < BINARY_DIGITS; k++, j++) {
            temp = input[i] % 2;
            input[i] = input[i] / 2;
            if (temp != 0) {
                output[i][j] = 1;
            } else {
                output[i][j] = 0;
            }
        }
    }
    return output;
}

int **getnetid(int **ip, int **subnet)
{
    int *octet = (int*)malloc(BINARY_DIGITS * sizeof(int));
    int **netid = (int**)malloc(IP_ADDR_SEGMENTS * sizeof(octet));
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        netid[i] = malloc(BINARY_DIGITS * sizeof(int));
    }
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        for (int k = 0, j = (BINARY_DIGITS - 1); k < BINARY_DIGITS; k++, j--) {
            if ((ip[i][j] == 1) && (subnet[i][j] == 1)) {
                netid[i][j] = 1;
            } else {
                netid[i][j] = 0;
            }
        }
    }
    return netid;
}

int binarytodecimal(int *input)
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
    return result;
}

void printbinaryaddress(int **binary)
{
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        for (int j = (BINARY_DIGITS - 1); j >= 0; j--) {
            printf("%d", binary[i][j]);
        }
        printf(" ");
    }
}

char *getvalidinput(char *prompttext, regex_t *regex)
{
    char *inputstring = (char*)malloc(15 * sizeof(char));
    while (1) {
        printf(prompttext);
        scanf("%s", inputstring);
        if (0 == regexec(regex, inputstring, 0, NULL, 0)) {
            char **chars = splitup(inputstring);
            int *decimal = todecimal(chars);
            if (0 == iswithinrange(decimal)) {
                break;
            } else {
                resetarrays(chars, decimal);
                printf(ERROR_ADDR_OUT_OF_RANGE);
            }
        } else {
                printf(ERROR_ADDR_MALFORMED);
        }
    }
    return inputstring;
}

void resetarrays(char **chars, int *decimal)
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

int iswithinrange(int *ip)
{
    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        if (0 > ip[i] || ip[i] > 255) {
           return -1;
        }
    }
    return 0;
}

void printresulttable(int **ip, int **subnet, int **net)
{
    printf("\n");
    printf("IP:\t\t");
    printbinaryaddress(ip);

    printf("\nSubnet mask:\t");
    printbinaryaddress(subnet);
    printf("\n");

    printf("\t\t-----------------------------------\n"); printf("Net ID:\t\t");
    printbinaryaddress(net);
    printf("\n\n");

    printf("Net ID as IP address:\t");

    for (int i = 0; i < IP_ADDR_SEGMENTS; i++) {
        printf("%d", binarytodecimal(net[i]));
        if (i < (IP_ADDR_SEGMENTS - 1)) {
            printf(".");
        }
    }
    printf("\n");
}
