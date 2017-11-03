#include <stdio.h>
#include "../beebitcpabe.h"

int main(void){

	if(cpabe_fenc("./pubKey", "./data", "role <= 2", "default") == -1){
		printf("ENC FAILED\n");
		return -1;
	}

	printf("ENC SUCCESS\n");
	return 0;
}

