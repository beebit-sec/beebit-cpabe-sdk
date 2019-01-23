#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../beebitcpabe.h"

int main(int argc, char** argv) {

	if(argc < 3) {
		fprintf(stderr, "Usage: cpabe-setup [pk] [mk]\n");
		fprintf(stderr, "pk: path to generate public key\n");
		fprintf(stderr, "mk: path to generate master key\n");
		return EXIT_FAILURE;
	}

	char* pk = argv[1];
	char* mk = argv[2];

	if(cpabe_setup(pk, mk) == -1) {
		fprintf(stderr, "Setup failed!\n");
		return EXIT_FAILURE;
	}

	fprintf(stderr, "Setup success!\n");
	fprintf(stderr, "Public Key: %s\n", pk);
	fprintf(stderr, "Master Key: %s\n", mk);
	return EXIT_SUCCESS;
}
