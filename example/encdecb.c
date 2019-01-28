#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../beebitcpabe.h"

int main(int argc, char** argv) {

	if(argc < 4) {
		fprintf(stderr, "Usage: cpabe-encdecb [pk] [sk] [ap]\n");
		fprintf(stderr, "pk: path to public key\n");
		fprintf(stderr, "sk: path to secret key\n");
		fprintf(stderr, "ap: access policy\n");
		return EXIT_FAILURE;
	}

	char* pk = argv[1];
	char* sk = argv[2];
	char* ap = argv[3];

	char pt[256];

	fprintf(stderr, "Plain Text:\n");
	scanf("%[^\n]s)", pt);
	
	// ENCRYPTION PROCESS
	cpabebuf* ctb = new_cpabebuf();
	cpabe_enc_b(pk, pt, strlen(pt), ap, ctb);
	if(ctb == NULL) {
		fprintf(stderr, "Encrypt failed!\n");
		return EXIT_FAILURE;
	}
	fprintf(stderr, "Encrypt success!\n");
	fprintf(stderr, "[ct len = %d])\n", ctb->len);

	cpabebuf* ptb = new_cpabebuf();
	ptb = cpabe_dec_b(pk, sk, ctb->data, ctb->len, ptb);
	if(ptb == NULL) {
		fprintf(stderr, "Decrypt failed!\n");
		return EXIT_FAILURE;

	}
	fprintf(stderr, "Decrypt success!\n");
	fprintf(stderr, "%s [pt len = %d])\n", ptb->data, ptb->len);
	
	free_cpabebuf(ctb);
	free_cpabebuf(ptb);

	return EXIT_SUCCESS;
}

