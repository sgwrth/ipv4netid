#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "ipv4netid.h"
#define PROMPT_FOR_IP "Enter IP address: "
#define PROMPT_FOR_SUBNET "Enter subnet mask: "

int main(int argc, char **argv)
{
    regex_t regex;
    if (0 == initregex(&regex)) {
        char *ipstring = getvalidinput(PROMPT_FOR_IP, &regex);
        char * subnetstring = getvalidinput(PROMPT_FOR_SUBNET, &regex);
        regfree(&regex);
        int **ipbinary = tobinary(todecimal(splitup(ipstring)));
        free(ipstring);
        int **subnetbinary = tobinary(todecimal(splitup(subnetstring)));
        free(subnetstring);
        int **netid = getnetid(ipbinary, subnetbinary);
        printresulttable(ipbinary, subnetbinary, netid);
        free(ipbinary);
        free(subnetbinary);
        free(netid);
        return 0;
    }
    return -1;
}
