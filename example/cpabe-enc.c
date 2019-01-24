#include <stdio.h>
#include <stdlib.h>
#include "../beebitcpabe.h"

int main(int argc, char** argv) {

	if(argc < 5) {
		fprintf(stderr, "Usage: cpabe-enc [pk] [pt] [ap] [ct]\n");
		fprintf(stderr, "pk: path to public key\n"); 
		fprintf(stderr, "pt: path to file (plain text)\n"); 
		fprintf(stderr, "ap: access policy\n"); 
		fprintf(stderr, "ct: path to encrypted file (cipher text)\n"); 
		return EXIT_FAILURE;
	}

	char *pk = argv[1];
	char *pt = argv[2];
	char *ap = argv[3];
	char *ct = argv[4];

	if(cpabe_fenc(pk, pt, ap, ct) == -1){
		fprintf(stderr, "Encrypt failed!\n");
		return EXIT_FAILURE;
	}

	fprintf(stderr, "Encrypt success!\n");
	fprintf(stderr, "File (%s) encrypted to file (%s) with policy (%s).\n", pt, ct, ap);
	return EXIT_SUCCESS;
}
