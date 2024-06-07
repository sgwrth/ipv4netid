#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "ipv4netid.h"
#define BINARY_DIGITS 8
#define IP_SEGMENTS 4
#define MAX_DIGITS_IN_IP_SEGMENT 3
#define IP_MAX_LENGTH 15
#define MAX_VAL_8_BIT 255
#define REGEX_FOR_IP "^[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}$"
#define ERROR_ADDR_OUT_OF_RANGE "Sorry, address out of range!\n"
#define ERROR_ADDR_MALFORMED "Sorry, wrong format!\n"

int init_regex(regex_t *regex)
{
	return regcomp(regex, REGEX_FOR_IP, REG_EXTENDED);
}

char **splitup(char *string)
{
	char *values = malloc(MAX_DIGITS_IN_IP_SEGMENT * sizeof(char));
	char **output = malloc(IP_SEGMENTS * sizeof(values));
	for (int i = 0; i < IP_SEGMENTS; i++) {
		output[i] = malloc(MAX_DIGITS_IN_IP_SEGMENT * sizeof(char));
	}
	int m = 0;
	int n = 0;
	for (int i = 0; i <= MAX_DIGITS_IN_IP_SEGMENT; i++) {
		while ((string[n] != '.') && (string[n] != '\0')) {
			output[i][m] = string[n];
			m++;
			n++;
		}
		m = 0;
		n++;
	}
	return output;
}

int *to_decimal(char **input)
{
	int *output = malloc(IP_SEGMENTS * sizeof(int));
	for (int i = 0; i < IP_SEGMENTS; i++) {
		output[i] = atoi(input[i]);
	}
	return output;
}

int **to_binary(int *input)
{
	int *octet = malloc(BINARY_DIGITS * sizeof(int));
	int **output = malloc(IP_SEGMENTS * sizeof(octet));
	for (int i = 0; i < IP_SEGMENTS; i++) {
		output[i] = malloc(BINARY_DIGITS * sizeof(int));
	}
	int temp;
	for (int i = 0; i < IP_SEGMENTS; i++) {
		for (int j = 0; j < BINARY_DIGITS; j++) {
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

int **get_netid(int **ip, int **subnet)
{
	int *octet = malloc(BINARY_DIGITS * sizeof(int));
	int **netid = malloc(IP_SEGMENTS * sizeof(octet));
	for (int i = 0; i < IP_SEGMENTS; i++) {
		netid[i] = malloc(BINARY_DIGITS * sizeof(int));
	}
	for (int i = 0; i < IP_SEGMENTS; i++) {
		for (int j = BINARY_DIGITS - 1; j >= 0 ; j--) {
			if ((ip[i][j] == 1) && (subnet[i][j] == 1)) {
				netid[i][j] = 1;
			} else {
				netid[i][j] = 0;
			}
		}
	}
	return netid;
}

int binary_to_decimal(int *input)
{
	int factor = 1;
	int *temp = malloc(BINARY_DIGITS * sizeof(int));
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

void print_binary_adress(int **binary)
{
	for (int i = 0; i < IP_SEGMENTS; i++) {
		for (int j = (BINARY_DIGITS - 1); j >= 0; j--) {
			printf("%d", binary[i][j]);
		}
		printf(" ");
	}
}

char *get_valid_input(char *prompt_text, regex_t *regex)
{
	char *string = malloc(15 * sizeof(char));
	while (1) {
		printf("%s", prompt_text);
		scanf("%s", string);
		if (0 == regexec(regex, string, 0, NULL, 0)) {
                        if (0 == check_range(string)) {
                                break;
                        } else {
                                printf(ERROR_ADDR_OUT_OF_RANGE);
                        }
		} else {
                        printf(ERROR_ADDR_MALFORMED);
		}
	}
	return string;
}

int check_range(char *string)
{
        char **chars = splitup(string);
        int *decimal = to_decimal(chars);
        return (1 == is_within_8bit_range(decimal)) ? 0 : -1;
}

int is_within_8bit_range(int *ip)
{
	for (int i = 0; i < IP_SEGMENTS; i++) {
		if (0 > ip[i] || ip[i] > MAX_VAL_8_BIT) {
			return -1;
		}
	}
	return 1;
}

void print_result_table(int **ip, int **subnet, int **net)
{
	printf("\nIP:\t\t");
	print_binary_adress(ip);

	printf("\nSubnet mask:\t");
	print_binary_adress(subnet);

	printf("\n\t\t-----------------------------------\nNet ID:\t\t");
	print_binary_adress(net);
	printf("\n\nNet ID as IP address:\t");

	for (int i = 0; i < IP_SEGMENTS; i++) {
		printf("%d", binary_to_decimal(net[i]));
		if (i < IP_SEGMENTS - 1) {
			printf(".");
		}
	}
	printf("\n");
}
