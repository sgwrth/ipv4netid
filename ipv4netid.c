#include <stdio.h>
#include <string.h>
#define BIN 8
#define DEC 4
#define IPLEN 16

char ip_adr[IPLEN];
char subnet_mask[IPLEN];
int len_ip;
int len_subnet;
int m, n, x;
int ip_intArray[DEC][BIN];
int subnet_intArray[DEC][BIN];
int netzID[DEC][BIN];
char ip[DEC][DEC];
char subnet[DEC][DEC];
int ip_int[DEC];
int subnet_int[DEC];

void splitIP();
int atoi();
void conv2bin();
void ausgabeBin();
void netID();
void convBin2dec();

int main()
{

    printf("Bitte geben Sie die IP-Adresse ein: ");
    scanf("%s", &ip_adr);
    len_ip = strlen(ip_adr) - 3;
    printf("Laenge IP: \t%d\n\n", len_ip);
  
    splitIP(ip_adr, ip);

    /* Umwandeln der char-Arrays in Dezimalzahlen (int-Werte) */
    for (n = 0; n <= 3; n++) {
        ip_int[n] = atoi(ip[n]);
    }

    conv2bin(ip_int, ip_intArray);
      
    printf("Bitte geben Sie die Subnetmaske ein: ");
    scanf("%s", &subnet_mask);
    len_subnet = strlen(subnet_mask) - 3;
    printf("Laenge Subnet: \t%d\n\n", len_subnet);

    splitIP(subnet_mask, subnet);
    
    /*  Umwandeln der char-Arrays in Dezimalzahlen (int-Werte) */
    for (n = 0; n <= 3; n++) {
        subnet_int[n] = atoi(subnet[n]);
    }
  
    conv2bin(subnet_int, subnet_intArray);

    netID(ip_intArray, subnet_intArray, netzID);
    
    printf("IP:\t");
    for (m = 0; m <= 3; m++) {
        for (n = 7; n >= 0; n--) {
            printf("%d", ip_intArray[m][n]);
        }
        printf(" ");
    }

    printf("\nSubnet:\t");
    for (m = 0; m <= 3; m++) {
        for (n = 7; n >= 0; n--) {
            printf("%d", subnet_intArray[m][n]);
        }
        printf(" ");
    }
    printf("\n");

    printf("\t-----------------------------------\n");

    printf("Net-ID:\t");
    for (m = 0; m <= 3; m++) {
        for (n = 7; n >= 0; n--) {
            printf("%d", netzID[m][n]);
        }
        printf(" ");
    }
    printf("\n\n");

    printf("Netz-ID als IP-Adresse:\t");
    for (n = 0; n <= 3; n++) {
        convBin2dec(netzID[n]);
        if (n < 3) {
            printf(".");
        }
    }
    printf("\n");
    return 0;
}

void splitIP(char input[IPLEN], char output[DEC][DEC])
{
    int posNr = 0;
    int m = 0;
    int n = posNr;
    int j;
    for (j = 0; j <= 3; j++) {
        while ((input[n] != '.') && (input[n] != '\0')) {
            output[j][m] = input[n];
            posNr++;
            m++;
            n++;
        }
        posNr++;
        n = posNr;
        m = 0;
    }
}

void conv2bin(int input[], int output[][x])   /* warum x bei output[][x] ?  */
{
    int m = 0;
    int n = 0;
    int zwErg;
    for (m = 0; m <= 3; m++) {
        int runde;
        for (runde = 1; runde <= BIN; runde++) {
            zwErg = input[m] % 2;
            input[m] = input[m] / 2;
            if(zwErg != 0) {
                output[m][n] = 1;
            } else {
                output[m][n] = 0;
            }
            n++;
        }
    }
}

void ausgabeBin(int output[][BIN])
{
    int m;
    int n;
    for (m = 0; m <= 3; m++) {
        printf("ip%d:\t", m);
        for (n = 7; n >= 0; n--) {		/* invertierte Ausgabe */
            printf("%d", output[m][n]);
        }
        printf(" ");
    }
    printf("\n");
}

void netID(int ipArray[][BIN], int subnetArray[][BIN], int netzArray[][BIN])
{
    int p;
    for (p = 0; p <= 3; p++) {
        int runde;
        int q;
		for (runde = 1, q = 7; runde <= BIN; runde++, q--) {
			if ((ipArray[p][q] == 1) && (subnetArray[p][q] == 1)) {
				netzArray[p][q] = 1;
			} else {
				netzArray[p][q] = 0;
			}
		}
    }
}

void convBin2dec(int input[BIN])
{
    int erg;
    int m = 1;
    int n;
    int zwWert[BIN];
    for (n = 0; n <= 7; n++) {
        zwWert[n] = input[n] * m;
        m = m * 2;
    }
    erg = zwWert[BIN - 1];
    for (n = 6; n >= 0; n--) {
        erg = erg + zwWert[n];
    }
    printf("%d", erg);
}
