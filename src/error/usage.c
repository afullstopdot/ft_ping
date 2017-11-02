#include <ping.h>

/*
** dump the correct usage
*/

void    dump_usage(void)
{

	/*
	** Dump the program usage
	*/

    printf("usage: ping [ [ -v ] [ -h ] ] <hostname>\n");

    /*
    ** Exit
    */

	exit(EXIT_SUCCESS);
}