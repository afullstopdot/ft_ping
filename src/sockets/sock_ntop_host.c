# include <ping.h>

#ifdef	HAVE_SOCKADDR_DL_STRUCT
    #include	<net/if_dl.h>
#endif

/*
** Convert IPv4/IPv6 addresses from binary to text form
*/

char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    /*
    ** Unix domain is the largest size
    */

    static char str[128];

    /*
    ** Switch family
    */

	switch (sa->sa_family) {

        /*
        ** IPv4
        */

        case AF_INET: {
            struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

            if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
                return(NULL);
            return(str);
        }

        /*
        ** IPv6
        */

    #ifdef	IPV6
        case AF_INET6: {
            struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

            if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
                return(NULL);
            return(str);
        }
    #endif

        /*
        ** default action, unknow family
        */

        default:
            snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d",
                    sa->sa_family, salen);
            return(str);
	}
    return (NULL);
}

char *ft_sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
	char	*ptr;

	if ( (ptr = sock_ntop_host(sa, salen)) == NULL)
        ft_fatal_error("sock_ntop_host error");
	return(ptr);
}