#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../beebitcpabe.h"

int main(int argc, char** argv) {

	if(argc < 4) {
		fprintf(stderr, "Usage: cpabe-encdec [pk] [sk] [ap]\n");
		fprintf(stderr, "pk: path to public key\n");
		fprintf(stderr, "sk: path to secret key\n");
		fprintf(stderr, "ap: access policy\n");
		return EXIT_FAILURE;
	}

	char* pk = argv[1];
	char* sk = argv[2];
	char* ap = argv[3];

	char pt[256];
	char* ct = NULL;

	fprintf(stderr, "Plain Text:\n");
	scanf("%[^\n]s)", pt);
	
	// ENCRYPTION PROCESS
	int len = 0;
	len = cpabe_enc(pk, pt, strlen(pt), ap, &ct);
	if(len == -1){
		fprintf(stderr, "Encrypt failed!\n");
		return EXIT_FAILURE;
	}
	fprintf(stderr, "Encrypt success!\n");
	fprintf(stderr, "[ct len = %d])\n", len);

	// DECRYPTION PROCESS
	char* result = NULL;
	
	len = cpabe_dec(pk, sk, ct, len, &result);
	if(len == -1){
		fprintf(stderr, "Decrypt failed!\n");
		return EXIT_FAILURE;
	}
	result[len] = '\0';	
	fprintf(stderr, "Decrypt success!\n");
	fprintf(stderr, "%s [pt len = %d])\n", result, len);

	return EXIT_SUCCESS;
}

