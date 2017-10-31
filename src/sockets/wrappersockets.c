#include "ping.h"

/*
** get time of the day wrapper
*/

void    ft_gettimeofday(struct timeval *tv, void *foo)
{
	if (gettimeofday(tv, foo) == -1)
		ft_fatal_error("gettimeofday error");
	return ;
}

/*
** calloc wrapper
*/

void *ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	if ((ptr = calloc(n, size)) == NULL)
        ft_fatal_error("calloc error");
	return (ptr);
}

/*
** sendto wrapper
*/

void	ft_sendto(int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen)
{
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
		ft_fatal_error("sendto error");
	return ;
}