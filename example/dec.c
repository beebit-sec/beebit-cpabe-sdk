#include <stdio.h>
#include <stdlib.h>
#include "../beebitcpabe.h"

int main(int argc, char** argv) {

	if(argc < 5) {
		fprintf(stderr, "Usage: cpabe-dec [pk] [sk] [ct] [pt]\n");
		fprintf(stderr, "pk: path to public key\n");
		fprintf(stderr, "sk: path to secret ket\n");
		fprintf(stderr, "ct: path to encrypted file (cipher text)\n");
		fprintf(stderr, "pt: path to original file (plain text)\n");
		return EXIT_FAILURE;
	}

	char* pk = argv[1];
	char* sk = argv[2];
	char* ct = argv[3];
	char* pt = argv[4];

	if(cpabe_fdec(pk, sk, ct, pt) == -1) {
		fprintf(stderr, "Decrypt failed!\n");
		return EXIT_FAILURE;
	}
	fprintf(stderr, "Decrypt success!\n");
	fprintf(stderr, "File (%s) decrypted to file (%s).\n", ct, pt);
	return EXIT_SUCCESS;
}

