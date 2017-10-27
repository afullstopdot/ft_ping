#include	"ping.h"

#ifdef	HAVE_SOCKADDR_DL_STRUCT
#include	<net/if_dl.h>
#endif

static char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{

	/*
	** Unix domain is largest
	*/

    static char str[128];

	switch (sa->sa_family) {
		case AF_INET: {
			struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

			if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
				return(NULL);
			return(str);
		}
#ifdef	IPV6
		case AF_INET6: {
			struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

			if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
				return(NULL);
			return(str);
		}
#endif
		default:
			snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d", sa->sa_family, salen);
			return(str);
	}
    return (NULL);
}

/*
** inet_pton wrapper with IPv4 and IPv6 support
*/

char 		*ft_wsock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
	char	*ptr;

	if ((ptr = sock_ntop_host(sa, salen)) == NULL)
	{

		/*
		** inet_pton sets errno
		*/

		printf("sock_ntop_host error");
		exit(EXIT_FAILURE);
	}
	return(ptr);
}
