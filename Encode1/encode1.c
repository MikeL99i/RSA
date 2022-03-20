#include <stdio.h>
#include "bitfile.h"
#include "mod_arith.h"

#pragma warning(disable:4996)


int main()
{
	BITFILE* input;
	FILE* output;
	FILE* e_key;
	int i;
	int blocksize;
	int N, E; // Modul N
	unsigned int block, restblock;
	char string[100];


	input = bitopen("C:\\C++\\C++ Workspace\\POA_V7_A2\\Encode1\\test_i.txt", "rb");
	output = fopen("C:\\C++\\C++ Workspace\\POA_V7_A2\\Encode1\\test_o.txt", "wb");
	e_key = fopen("C:\\C++\\C++ Workspace\\POA_V7_A2\\Encode1\\s1.ne", "r");


	if (input == NULL || output == NULL || e_key == NULL)
	{
		printf("Error\n");
		return 0;
	}

	fgets(string, 100, e_key);
	sscanf(string, "%d", &N);
	blocksize = bits_required(N)-1;
	printf("Blocksize ist %d\n\n", blocksize);

	fgets(string, 100, e_key);
	sscanf(string, "%d", &E);
	//fprintf(output, "#%u\n", blocksize); // schreibt in die kodierte datei die blockgröße

	do {
		block = 0; // 0 da anfangs nichts in output datei steht und beim jedem durchlauf ein neuer block gebaut wird = 0 setzen
		i = bitreadblock(input, blocksize, &block); // block wird dabei 4 mal verändert
		//je nach dem wie oft bitread ausgeführt wurde wird ein entsprechender wert für i zurückgeliefert
		if (i < blocksize)
		{
			restblock = N + i;
			fprintf(output, "%u\n", restblock);
			break;
		}

		mod_power(block, E, N);
		fprintf(output, "%u\n", block);

	} while (i == blocksize); // läuft solange bitreadblock die gleich größe zurückliefert

	//fprintf(output, "#%d", blocksize); 

	bitclose(input);
	fclose(e_key);
	fclose(output);

	getch();
	return 0;
}



