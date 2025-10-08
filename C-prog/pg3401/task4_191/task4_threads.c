#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

/* This file has been created by EWA, and is part of task 4 on the exam for PG3401 2025*/
/* Original code credited to Dan Bernstein*/
int Task2_SimpleDjb2Hash(FILE *f, unsigned int *piHash) {
	unsigned int hash = 5381;
    	int iCharacter = 0;
    	rewind(f);
   	 do {
        	iCharacter = fgetc(f);
        	if (iCharacter == 0 || iCharacter == EOF) break;
        	hash = ((hash << 5) + hash) + (char)iCharacter;
    	} while (iCharacter != EOF);
    	*piHash = hash;
    	rewind(f);
    	return 0;
}

/* This file has been created by EWA, and is part of task 4 on the exam for PG3401 2025*/
/* Original code credited to David Wheeler and Roger Needham */
/* Documentation: https://www.schneier.com/wp-content/uploads/2015/03/TEA-2.c */ 
void encipher(unsigned int *const v, unsigned int *const w, const unsigned int *const k) {
    	register unsigned int y = v[0], z = v[1], sum = 0;
    	register unsigned int delta = 0x9E3779B9;
    	register unsigned int a = k[0], b = k[1], c = k[2], d = k[3];
    	for (int n = 0; n < 32; n++) {
        	sum += delta;
        	y += ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
        	z += ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
    	}
    	w[0] = y; w[1] = z;
}

// Struct for passing data to threads
typedef struct {
    	const char *filename; // File that is being processed
    	sem_t *sem;           // Semaphore for thread sync
} 	ThreadData;

// Thread A opens the file, signals completion, then exits 
void* thread_A(void* arg) {
    	ThreadData *data = (ThreadData*)arg;
    	FILE *fp = fopen(data->filename, "rb");
    	if (!fp) {
        	perror("File open failed");
        	exit(EXIT_FAILURE);
    	}

    	fclose(fp);

    	// Signal that file open is done
    	sem_post(data->sem);

    	pthread_exit(NULL);
}

// Thread B waits for Thread A, then processes the file
void* thread_B(void* arg) {
    	ThreadData *data = (ThreadData*)arg;

    	// Wait for Thread A to finish
    	sem_wait(data->sem);

    	FILE *fp = fopen(data->filename, "rb");
    	if (!fp) {
        	perror("Failed to open the file for hashing or encryption");
        	pthread_exit(NULL);
    	}

    	// Computes the hash of the file contents 
    	unsigned int hash;
    	if (Task2_SimpleDjb2Hash(fp, &hash) != 0) {
        	perror("The hashing failed");
        	fclose(fp);
		pthread_exit(NULL);
    	}

    	// Write the hash value to the named output file
    	FILE *hash_fp = fopen("task4_pg2265.hash", "w");
    	if (!hash_fp) {
        	perror("Failed to open hash output file");
        	fclose(fp);
        	pthread_exit(NULL);
    	}
    	fprintf(hash_fp, "%u\n", hash);
    	fclose(hash_fp);

    	// Preparing for encryption, reads file, applying PKCS5 padding as asked in assignment
    	fseek(fp, 0, SEEK_END);
    	long file_size = ftell(fp);
    	rewind(fp);

    	unsigned char *file_data = malloc(file_size + 8); // for PKCS5 padding
    	if (!file_data) {
        	perror("Memory allocation failed");
        	fclose(fp);
        	pthread_exit(NULL);
    	}

    	size_t read_bytes = fread(file_data, 1, file_size, fp);
    	fclose(fp);

    	// Applying PKCS5 padding to make the size a multiple of 8 bytes
    	int padding = 8 - (read_bytes % 8);
    	for (int i = 0; i < padding; i++) {
        	file_data[read_bytes + i] = (unsigned char)padding;
    	}
    	size_t total_padded = read_bytes + padding;

    	// Encryption key
    	unsigned int key[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};

    	// This writes the encrypted data to the output file, perror if fail 
    	FILE *enc_fp = fopen("task4_pg2265.enc", "wb");
    	if (!enc_fp) {
        	perror("Failed to open encrypted output file");
        	free(file_data);
        	pthread_exit(NULL);
    	}

    	// Encrypting in 8 byte blocks
    	for (size_t i = 0; i < total_padded; i += 8) {
        	unsigned int v[2], w[2];
        	memcpy(v, &file_data[i], 8);
        	encipher(v, w, key);
        	fwrite(w, sizeof(unsigned int), 2, enc_fp);
    	}

    	fclose(enc_fp);
    	free(file_data);

    	pthread_exit(NULL);
}

// The main function that starts the sync of both threads, then waits for them to complete
int main(int argc, char *argv[]) {
    	if (argc != 2) {
        	fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        	exit(EXIT_FAILURE);
    	}

    	sem_t sem;
    	sem_init(&sem, 0, 0);

    	// Sharing data for both threads
    	ThreadData data = {
        	.filename = argv[1],
        	.sem = &sem
    	};

    	pthread_t tid_A, tid_B;

    	// Starting both threads
    	if (pthread_create(&tid_A, NULL, thread_A, &data) ||
        	pthread_create(&tid_B, NULL, thread_B, &data)) {
        	perror("Thread creation failed");
        	exit(EXIT_FAILURE);
    	}
    	// Waiting for both threads to finish
    	pthread_join(tid_A, NULL);
    	pthread_join(tid_B, NULL);

    	sem_destroy(&sem);

    	return 0;
}




