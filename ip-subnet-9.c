/*******************************************************************************
 * 
 *  NETZ-ID
 *  -------
 * 
 *  von:	sgwrth
 *  Datum:      09/2022 (letzte Aenderung: 03/2024)
 *  E-Mail:     -
 * 
 *  Sprache:    C
 * 
 *  Beschreibung:
 *  Das Programm ermittelt anhand einer eingebenen IPv4-Adresse und Subnet-
 *  maske die entsprechende Netz-ID. Dafuer werden die eingebene IP und
 *  die Subnetmaske zunaechst in das Binaerformat umgerechnet.  Der Anschau-
 *  lichkeit halber werden die Binaerwerte im Terminal ausgegeben.
 * 
 *  To do:
 *  - Abfangen von Fehleingaben
 *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#define BIN 8
#define DEC 4
#define IPLEN 16

char        ip_adr[IPLEN];
char        subnet_mask[IPLEN];
int         len_ip;
int         len_subnet;
int         m, n, x;
int         ip_intArray[DEC][BIN],
            subnet_intArray[DEC][BIN],
            netzID[DEC][BIN];
char        ip[DEC][DEC],
            subnet[DEC][DEC];
int         ip_int[DEC],
            subnet_int[DEC];
int         atoi();
void        ausgabeBin();
void        conv2bin();
void        convBin2dec();
void        netID();
void        splitIP();

/* -------------------------------------------------------------------------- */

/*
 *  Aufteilen der eingegebenen IPv4-Adresse:
 *  ----------------------------------------
 *  Die IP wird in ihre vier Teile gesplittet und in ein zweidimensionales
 *  Charakter-Array geschrieben.
 */
void splitIP(char input[IPLEN], char output[DEC][DEC])
{
    int posNr = 0;                      /* Anfangsposition zum Auslesen */
    int m = 0;
    int n = posNr;
    int j;
    for (j = 0; j <= 3; j++) {
        /*
         *  Die IP wird bis zum "."-Zeichen oder dem Eingabeende \0 durch-
         *  gegangen; jeder Wert wird als char in ein Array geschrieben.
         *  Der Vorgang wird wiederholt, wobei bei jedem neuem Durchgang
         *  am Ende des vorherigen neu angesetzt wird.
         */
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

/*
 *  Dezimal nach Binaer:
 *  --------------------
 *  Wandelt Dezimalzahl-Array ins Binaerformat (zweidimensionales int-Array) um.
 *  Zur Umrechnung wird die jew. Dezimalzahl zunaechst durch zwei geteilt;
 *  bleibt ein Rest, wird als Binaerwert eine 1 gesetzt, sonst eine 0.  Mit dem
 *  Ergebnis der Division (ggf. auf ganze Zahl abgerundet) wird die Rechnung
 *  wiederholt, bis die acht Binaerwerte ermittelt sind.
 */
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

/*
 *  Ausgabe des Binaerzahl-Arrays:
 *  ------------------------------
 *  Die zu Binaerwerten umgerechtete IP-Adresse wird ausgegeben.  Die Ausgabe
 *  der im Array gespeicherten Binaerwerte muss dabei in umgekehrter Reihenfolge
 *  erfolgen, um korrekt angezeigt zu werden.
 */
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

/*
 *  Errechnung der Netz-ID:
 *  -----------------------
 *  Die Funktion nimmt die IP-Adresse und Subnetmaske in Binaerform (zwei-
 *  dimensionale int-Arrays) als input an und ermittelt die Netz-ID ebenfalls
 *  in Binaerform: an jeder Stelle, an der IP und Subnetmaske beide den Wert 1
 *  haben, wird auch in der Netz-ID die 1 gesetzt, sonst 0.
 */
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

/*
 *  Umrechnen von binaer nach dezimal:
 *  ----------------------------------
 *  Umrechnung einer achtstellingen Binaerzahl in einen Dezimalwert.  Dient
 *  dazu, die ermittelte Netz-ID im Binaerformat in das uebliche IP-Format um-
 *  zuwandeln.
 */
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

/* ========================================================================== */

int main() {

    /* Eingabe der IP-Adresse und Rueckgabe der char-Anzahl (exkl. Punkten) */
    printf("Bitte geben Sie die IP-Adresse ein: ");
    scanf("%s", &ip_adr);
    len_ip = strlen(ip_adr) - 3;
    printf("Laenge IP: \t%d\n\n", len_ip);
  
    /* Aufsplitten der IP in vier char-Arrays */
    splitIP(ip_adr, ip);

    /* Umwandeln der char-Arrays in Dezimalzahlen (int-Werte) */
    for (n = 0; n <= 3; n++) {
        ip_int[n] = atoi(ip[n]);
    }

    /* Umwandeln der Dezimalzahlen in Binaerzahlen */
    conv2bin(ip_int, ip_intArray);
      
	/* Eingabe der Subnet-Maske und Rueckgabe der char-Anzahl (exkl. Punkten) */
    printf("Bitte geben Sie die Subnetmaske ein: ");
    scanf("%s", &subnet_mask);
    len_subnet = strlen(subnet_mask) - 3;
    printf("Laenge Subnet: \t%d\n\n", len_subnet);

    /*  Aufsplitten der Subnetmaske in vier char-Arrays */
    splitIP(subnet_mask, subnet);
    
    /*  Umwandeln der char-Arrays in Dezimalzahlen (int-Werte) */
    for (n = 0; n <= 3; n++) {
        subnet_int[n] = atoi(subnet[n]);
    }
  
    /* Umwandeln der Dezimalzahlen in Binaerzahlen */
    conv2bin(subnet_int, subnet_intArray);

    /* Errechnung der Netz-ID */
    netID(ip_intArray, subnet_intArray, netzID);
    
    /* Output der IP-Adresse als Binaerzahlen */
    printf("IP:\t");
    for (m = 0; m <= 3; m++) {
        for (n = 7; n >= 0; n--) {
            printf("%d", ip_intArray[m][n]);
        }
        printf(" ");
    }

    /*  Output der Subnetmaske als Binaerzahlen */
    printf("\nSubnet:\t");
    for (m = 0; m <= 3; m++) {
        for (n = 7; n >= 0; n--) {
            printf("%d", subnet_intArray[m][n]);
        }
        printf(" ");
    }
    printf("\n");

    printf("\t-----------------------------------\n");

    /*  Output der Netz-ID */
    printf("Net-ID:\t");
    for (m = 0; m <= 3; m++) {
        for (n = 7; n >= 0; n--) {
            printf("%d", netzID[m][n]);
        }
        printf(" ");
    }
    printf("\n\n");

    /* Output der Netz-ID als IPv4-Adresse */
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
