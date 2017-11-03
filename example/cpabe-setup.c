#include <stdio.h>
#include "../beebitcpabe.h"

int main(void){

	if(cpabe_setup("./pubKey","./mstKey") == -1){
		printf("SETUP FAILED!\n");
		return -1;
	}
	printf("SETUP SUCCESS\n");
	return 0;
}
