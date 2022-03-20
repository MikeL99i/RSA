#ifndef __BITFILE__
#define __BITFILE__

#include <stdio.h>  // wird f�r malloc ben�tigt


// Datenstruktur
typedef struct {
	FILE* file;
	unsigned int buffer;
	unsigned int bitanz;
} BITFILE;


/*Funktion: �ffnet eine Datei zum Lesen oder schreiben
  fname: String mit Dateiname
  mode: String mit Modus (sinnvoll: "rb" f�r Lesen oder "wb" f�r Schreiben)
  R�ckgabe: Zeiger auf Kontrollstruktur vom Datentyp BITFILE
  Info: Der Speicher fuer die Datenstruktur wird dynamisch allokiert */
BITFILE* bitopen(const char* fname, const char* mode);

/* Funktion: schliesst die Datei gibt den Speicherplatz f�r
   die Kontrollstruktur wieder frei
   Parameter: Zeiger auf die Kontrollstruktur
  (dieser Parameter wird bei den folgenden Funktionen nicht mehr erw�hnt) */
void bitclose(BITFILE* bit_file);

/* Funktion: schreibt die restlichen Bits aus dem Buffer
  (falls noch welche darin sind) in die Datei
   muss bei Dateien, die zum Schreiben ge�ffnet sind, vor bitclose aufgerufen werden */
void bitflush(BITFILE* bit_file);

/* Funktion: schreibt ein einzelnes Bit
   Falls value != 0 wird eine 1 geschrieben
   Falls value == 0 wird eien 0 geschrieben */
void bitwrite(BITFILE* bit_file, unsigned int value);

/* Funktion: liest ein einzelnes Bit
   Falls gelesenes Bit 1 ist, wird der Wert 1 zur�ckgegeben
   Falls gelesenes Bit 0 ist, wird der Wert 0 zur�ckgegeben */
unsigned int bitread(BITFILE* bit_file);

/* Funktion: schreibt mehrere Bits
   Parameter anz: Anzahl der Bits
   Parameter Block: Adresse im Speicher, wo die zu schreibenden Bits abgelegt sind */
void bitwriteblock(BITFILE* fd, unsigned int anz, unsigned int* block);

/* Funktion: liest mehrere Bits
   Parameter anz: Anzahl der Bits
   Parameter Block: Adresse im Speicher, wo die zu lesenden Bits abgelegt werden
   R�ckgabe: Anzahl der tats�chlich gelesenen Bits - kann kleiner sein als anz */
unsigned int bitreadblock(BITFILE* fd, unsigned int anz, unsigned int* block);

#endif /* __BITFILE__ */