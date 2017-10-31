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