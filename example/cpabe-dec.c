#include <stdio.h>
#include "../beebitcpabe.h"

int main(void){

	printf("=== DEC WITH NG KEY ===\n");
	if(cpabe_fdec("./pubKey","./secKey_ng","./data.cpabe") == -1){
		printf("DEC FAILED\n");
		//return -1;
	}

	printf("=== DEC WITH OK KEY ===\n");
	if(cpabe_fdec("./pubKey","./secKey_ok","./data.cpabe") == -1){
		printf("DEC FAILED\n");
		return -1;
	}
	printf("DEC SUCCESS\n");
	return 0;
}

