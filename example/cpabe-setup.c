#include <stdlib.h>
#include <stdio.h>
#include "../beebitcpabe.h"

int main(void)
{
	if(cpabe_setup("./pubKey","./mstKey") == EXIT_FAILURE)
	{
		printf("SETUP FAILED!\n");
		return EXIT_FAILURE;
	}
	printf("SETUP SUCCESS\n");
	return EXIT_SUCCESS;
}
