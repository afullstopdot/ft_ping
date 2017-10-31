#include "ping.h"

struct addrinfo     *ft_host_serv(const char *host, const char *serv, int family, int socktype)
{
    int             n;
    struct addrinfo hints;
    struct addrinfo *res;

    /*
    **
    */

    bzero (&hints, sizeof (struct addrinfo));

    /*
    ** always return canonical name
    */

    hints.ai_flags = AI_CANONNAME;

    /*
    ** AF_UNSPEC, AF_INET, AF_INET6, etc.
    */

    hints.ai_family = family;

    /*
    ** 0, SOCK_STREAM, SOCK_DGRAM, etc.
    */

    hints.ai_socktype = socktype;

    /*
    **
    */

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
        return (NULL);

    /*
    ** return pointer to first on linked list
    */

    return (res);
}