#include <stdio.h>
#include "../beebitcpabe.h"

int main(void)
{
	if(cpabe_keygen("./secKey_ok","./pubKey","./mstKey",3,"bob","teacher","role = 1") == -1){
		printf("OK KEYGEN ERROR\n");
		return -1;
	}
	printf("OK KEYGEN SUCCESS\n");

	char* p[] = {"alice","female","role = 3"};
	
	if(cpabe_vkeygen("./secKey_ng","./pubKey","./mstKey",3, p) == -1){
		printf("NG KEYGEN ERROR\n");
		return -1;
	}
	printf("NG KEYGEN SUCCESS\n");
	
	return 0;
}
