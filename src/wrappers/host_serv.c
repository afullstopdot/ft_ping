#include "ping.h"

static struct addrinfo 	*host_serv(const char *host, const char *serv, int family, int socktype)
{
	int				n;
	struct addrinfo	hints;
	struct addrinfo	*res;

	/*
	** Clear addrinfo
	*/

	bzero(&hints, sizeof(struct addrinfo));

	/*
	** Always return canonical name
	*/

	hints.ai_flags = AI_CANONNAME;

	/*
	** AF_UNSPEC, AF_INET, AF_INET6, etc.
	*/

	hints.ai_family = family;

	/*
	**  0, SOCK_STREAM, SOCK_DGRAM, etc.
	*/

	hints.ai_socktype = socktype;

	/*
	** Get address info of host, will return a linked list of each iP address related to said host
	*/

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		return (NULL);

	/*
	** return pointer to first on linked list
	*/
	
	return (res);
}

/*
 * There is no easy way to pass back the integer return code from
 * getaddrinfo() in the function above, short of adding another argument
 * that is a pointer, so the easiest way to provide the wrapper function
 * is just to duplicate the simple function as we do here.
 */

struct addrinfo 		*ft_whost_serv(const char *host, const char *serv, int family, int socktype)
{
	int					n;
	struct addrinfo		*res;
	struct addrinfo		hints;

	/*
	** Clear address info stuct
	*/

	bzero(&hints, sizeof(struct addrinfo));

	/*
	** always return canonical name
	*/

	hints.ai_flags = AI_CANONNAME;

	/*
	** 0, AF_INET, AF_INET6, etc.
	*/

	hints.ai_family = family;

	/*
	** 0, SOCK_STREAM, SOCK_DGRAM, etc.
	*/

	hints.ai_socktype = socktype;

	/*
	** Get host address info, incase of failure print error message and exit
	*/

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
	{

		printf("host_serv error");
		exit(EXIT_SUCCESS);

	}

	/*
	** return pointer to first on linked list
	*/

	return(res);
}
