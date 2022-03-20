#include <stdio.h> 
#include <stdlib.h> 

#include "bitfile.h"

#pragma warning(disable:4996)


BITFILE* bitopen(const char* fname, const char* mode)
{
	BITFILE* bitfile;

	bitfile = (BITFILE*)malloc(sizeof(BITFILE));
	if (bitfile == NULL) return NULL;

	bitfile->file = fopen(fname, mode);
	if (bitfile->file == NULL) {
		free(bitfile);
		return NULL;
	}

	bitfile->bitanz = 0;
	return bitfile;
}


void bitclose(BITFILE* bitfile)
{
	fclose(bitfile->file);
	free(bitfile);
}

void bitflush(BITFILE* bitfile)
{
	printf("flushing %d bits\n", bitfile->bitanz);

	if (bitfile->bitanz == 0) return;  // nothing to do - no fill bits

	//printf ("buffer: %08x\n",bitfile->buffer);
		//bitfile->buffer &= ~(~0<<bitfile->bitanz); // clear fill bits (1 up to 7)
	//printf ("buffer modified: %08x\n",bitfile->buffer);
	fputc(bitfile->buffer, bitfile->file);
}

unsigned int bitread(BITFILE * bitfile)
{

	if (bitfile->bitanz == 0) { // wenn vor der Operation der Puffer leer ist -> dannnachfüllen 
		bitfile->buffer = fgetc(bitfile->file); // fgetc(quelle) = liest einzelne Zeichen aus der Datei - bspw. a aus der txt datei
		if (bitfile->buffer == EOF) return bitfile->buffer; //return EOF EOF Ende der Datei nachfüllen nicht mehr möglich
		bitfile->bitanz = 8; // char hat 8 bits
	}

	//
	if (bitfile->buffer & (1 << 8 - bitfile->bitanz--))  return 1; // Falls gelesenes Bit 1 ist, wird der Wert 1 zurückgegeben 1 wird um 8-bib nach links verschoben
	// & =  wenn beide true sind (nicht 0) dann return 1
	else return 0;

}


void bitwrite(BITFILE * bitfile, unsigned int value)
{
	unsigned int bitmask;
	if (value != 0)
	{
		bitfile->buffer = bitfile->buffer | 1 << bitfile->bitanz++;
	}
	else
	{
		bitmask = ~(1 << bitfile->bitanz); // das bit an der gesuchten stelle wird auf 0 gesetzt und alle anderen auf 1
		bitfile->buffer = bitfile->buffer & bitmask; // dadurch kann gezielt 1 bit gelöscht werden
		bitfile->bitanz++;
	}

	if (bitfile->bitanz == 8) // puffer voll?
	{
		fputc(bitfile->buffer, bitfile->file);
		bitfile->buffer = 0;
		bitfile->bitanz = 0;
	}


}


unsigned int bitreadblock(BITFILE * fd, unsigned int anz, unsigned int* block)
{
	int i;
	unsigned int bitval;
	for (i = 0; i < anz; i++) {
		//for (i=anz-1; i>=0; i--) {
		bitval = bitread(fd); // 1 oder 0
		if (bitval == EOF) break;
		if (bitval == 1) * block |= (1 << i); // bit an der stelle 1<<i wird gesetzt
		if (bitval == 0) * block &= ~(1 << i); // bit an der stelle 1<<i wird gelöscht
	}
	return i;
	//*block = *block >> (i+1);
	//return anz-1-i;
}

void bitwriteblock(BITFILE * fd, unsigned int anz, unsigned int* block)
{
	int i;
	for (i = 0; i < anz; i++) bitwrite(fd, *block & (1 << i)); //bit im block and der stelle 1<<i wird übernommen
	//for (i=anz-1; i>=0; i--) bitwrite (fd, *block&(1<<i) );
}