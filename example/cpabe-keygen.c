#include <stdio.h>
#include <stdlib.h>
#include "../beebitcpabe.h"

int main(int argc, char** argv) {

	if(argc < 6) {
		fprintf(stderr, "Usage: cpabe-keygen [sk] [pk] [mk] [no] [a1] ... [aN]\n");
		fprintf(stderr, "sk: path to generate secret key\n");
		fprintf(stderr, "pk: path to public key\n");
		fprintf(stderr, "mk: path to master key\n");
		fprintf(stderr, "no: number of attributes in generated secret key\n");
		fprintf(stderr, "a1 ... aN: attributes\n");
		return EXIT_FAILURE;
	}

	char *sk = argv[1];
	char *pk = argv[2];
	char *mk = argv[3];
	int no = atoi(argv[4]);

	char* attrs[no];
	int i;
	for(i=0;i<no;i++) {
		attrs[i] = argv[5+i];
		fprintf(stderr, "Attribute %d: %s\n", i, attrs[i]);
	}
	
	if(cpabe_vkeygen(sk, pk ,mk , no, attrs) == -1){
		fprintf(stderr, "Keygen failed!\n");
		return EXIT_FAILURE;
	}
	fprintf(stderr, "Keygen success!\n");
	
	return EXIT_SUCCESS;
}
