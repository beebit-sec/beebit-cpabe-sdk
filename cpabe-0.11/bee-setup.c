#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <pbc.h>
#include <pbc_random.h>

#include "bswabe.h"
#include "common.h"

char* pub_file = "pkey";
char* msk_file = "mkey";

int cpabe_setup(char* pub_pathname, char* msk_pathname)
{
	bswabe_pub_t* pub;
	bswabe_msk_t* msk;
	bswabe_setup(&pub, &msk);
	pub_file = pub_pathname;
	msk_file = msk_pathname;
	if(spit_file(pub_file, bswabe_pub_serialize(pub), 1) == EXIT_FAILURE)
	{
		 return EXIT_FAILURE;
	}
	if(spit_file(msk_file, bswabe_msk_serialize(msk), 1) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
