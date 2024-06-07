#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "ipv4netid.h"
#define PROMPT_FOR_IP "Enter IP address: "
#define PROMPT_FOR_SUBNET "Enter subnet mask: "

int main(int argc, char **argv)
{
    regex_t regex;
    if (0 == init_regex(&regex)) {
        char *ip_string = get_valid_input(PROMPT_FOR_IP, &regex);
        char * subnet_string = get_valid_input(PROMPT_FOR_SUBNET, &regex);
        regfree(&regex);
        int **ip_binary = to_binary(to_decimal(splitup(ip_string)));
        free(ip_string);
        int **subnet_binary = to_binary(to_decimal(splitup(subnet_string)));
        free(subnet_string);
        int **netid = get_netid(ip_binary, subnet_binary);
        print_result_table(ip_binary, subnet_binary, netid);
        free(ip_binary);
        free(subnet_binary);
        free(netid);
        return 0;
    }
    return -1;
}
