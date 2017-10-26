#include <ping.h>

/*
** dump the correct usage
*/

void    dump_usage(void)
{
    printf("Usage: ./ping <host>\
     \n\t-h sweepincrsize Specify the number of bytes to increment the size of ICMP payload after each sweep when sending sweeping pings. The default value is 1.\n");
    exit(EXIT_SUCCESS);
}