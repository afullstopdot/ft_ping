#include <ping.h>

/*
** Fatal error, end program
*/

void    ft_fatal_error(char *msg)
{
    printf("ft_ping: %s%s%s\n", C_RED, msg, C_RST);
    exit(EXIT_FAILURE);
}