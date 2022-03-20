#include <stdio.h>
#include "bitfile.h"
#include "mod_arith.h"
#include <math.h>

#pragma warning(disable:4996)


int main()
{
	BITFILE* input;
	FILE* d_key;
	BITFILE* output;
	int i;
	int blocksize;
	unsigned int block, restblock;
	char string[100];
	char key_string[100];
	int abbruch = 0;
	int N, D;
	int Bedingung;

	d_key = fopen("C:\\C++\\C++ Workspace\\POA_V7_A2\\Decode1\\s1.nd", "r");
	input = bitopen("C:\\C++\\C++ Workspace\\POA_V7_A2\\Decode1\\test.txt", "rb");
	output = bitopen("C:\\C++\\C++ Workspace\\POA_V7_A2\\Decode1\\testo.txt", "wb");

	if (input == NULL || output == NULL || d_key == NULL)
	{
		printf("Error\n");
		return 0;
	}

	fgets(string, 100, d_key);
	sscanf(string, "%d", &N);
	blocksize = bits_required(N);
	printf("Blocksize ist %d\n", blocksize);

	fgets(string, 100, d_key);
	sscanf(string, "%d", &D);
	printf("D = %d\n\n", D);

	Bedingung = pow(2, blocksize); // Damit erhöhe ich die blockgröße für zahlen mit 5 bits in ct
	printf("Bedingung = %d\n", Bedingung);

	//while (fgets(string, 100, input) != NULL)
	do
	{
		block = 0;
		i = bitreadblock(input, blocksize, &block);

		if (block >= N)
		{
			restblock = block - N;
			block = 0;
			i = bitreadblock(input, restblock, &block);
			block = mod_power(block, D, N);
			bitwriteblock(output, restblock-1, &block);
			break;
		}
		block = mod_power(block, D, N);
		bitwriteblock(output, blocksize-1, &block);


	/*	block = 0;
		//blocksize = bits_required(N) - 1;

		printf("string = %s", string);
		sscanf(string, "%d", &block);

		block = mod_power(block, D, N);
		printf("block = %d\n", block);

		if (block < Bedingung)
		{
			block = block << 1;
		}

		
		bitwriteblock(output, blocksize, &block);*/

	
	} while (i == blocksize);

	bitflush(output);
	bitclose(input);
	fclose(d_key);
	bitclose(output);


	getch();
}


