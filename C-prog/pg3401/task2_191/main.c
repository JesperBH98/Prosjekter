#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/task2_count.h"
#include "include/task2_hash.h"
#include "include/task2_sum.h"

// Structure to hold metadata
struct TASK2_FILE_METADATA {
	char szFileName[32]; // The filename is up to 31 chars +
    	int iFileSize; // File size in bytes
    	char byHash[4]; // 4 byte hash value for the file         
    	int iSumOfChars; // Count all the letters
    	char aAlphaCount[26];
};

int main() {
	const char *inputFile = "pgexam25_test.txt";
    	const char *outputFile = "pgexam25_output.bin";

    	// This opens the input file
    	FILE *f = fopen(inputFile, "rb");
    	if (!f) {
        	perror("Failed to open input file");
        	return 1;
    	}

    	// This initialize the metadata struct
    	struct TASK2_FILE_METADATA meta;
    	memset(&meta, 0, sizeof(meta));
    	strncpy(meta.szFileName, inputFile, sizeof(meta.szFileName)-1);

    	// Calls the three functions
	if (Task2_CountEachCharacter(f, meta.aAlphaCount) != 0) {
        	fclose(f);
        	perror("Failed to count characters");
        	return 1;
    	}
	
    	unsigned int hash;
    	if (Task2_SimpleDjb2Hash(f, &hash) != 0) {
        	fclose(f);
        	perror("Failed to compute hash");
        	return 1;
    	}
    	// Copies the hash as 4 bytes
    	meta.byHash[0] = (hash >>  0) & 0xFF;
    	meta.byHash[1] = (hash >>  8) & 0xFF;
   	meta.byHash[2] = (hash >> 16) & 0xFF;
    	meta.byHash[3] = (hash >> 24) & 0xFF;

    	int size, sum;
    	if (Task2_SizeAndSumOfCharacters(f, &size, &sum) != 0) {
        	fclose(f);
        	perror("Failed to compute size and sum");
        	return 1;
    	}
    	meta.iFileSize = size;
    	meta.iSumOfChars = sum;

    	// Closing the input file
    	fclose(f);

    	// Writes the struct to binary file, checks if fail to open the output file and gives acknowledgement after program is 		finished running
    	f = fopen(outputFile, "wb");
    	if (!f) {
        	perror("Failed to open output file");
        	return 1;
    	}
    	fwrite(&meta, sizeof(meta), 1, f);
    	fclose(f);

	printf("Program finished successfully!\n");
    	return 0;
}

