#include <glib.h>
#include <pbc.h>

#include "common.h"
#include "policy_lang.h"

int
main( int argc, char** argv )
{
	char* p;

	if( argc < 2 )
		die("specify policy\n");

	p = parse_policy_lang(argv[1]);

	printf("parsed to: %s\n", p);

	return 0;
}
