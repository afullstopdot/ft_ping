/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 15:11:14 by amarquez          #+#    #+#             */
/*   Updated: 2017/07/11 15:12:08 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
# define PING_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <libft.h>
# include <netinet/in_systm.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>

#ifdef	IPV6

# include	<netinet/ip6.h>
# include	<netinet/icmp6.h>

#endif

/*
** definitions
*/

# define TRUE 1
# define FALSE 0
# define BUFSIZE 1500
# define A_VERBOSE "-v"
# define A_SWEEPINCRSIZE "-h"

/*
** globals
*/

char	 sendbuf[BUFSIZE];

int		 datalen;			/* # bytes of data following ICMP header */
char	*host;
int		 nsent;				/* add 1 for each sendto() */
pid_t	 pid;				/* our PID */
int		 sockfd;
int		 verbose;

/*
** Runtime options
*/

typedef struct      s_env
{
    unsigned int    verbose;
    unsigned int    sweepincrsize;
    char            *host;
}                   t_env;

/*
** interpreter functions
*/

int                 init_env(int argc, char **argv, t_env *env);

/*
** error funcions
*/

void                dump_usage(void);

/*
** Signals
*/

Sigfunc             *ft_wsignal(int signo, Sigfunc *func);
struct addrinfo     *ft_whost_serv(const char *host, const char *serv, int family, int socktype);
char 		        *ft_wsock_ntop_host(const struct sockaddr *sa, socklen_t salen);

/*
** Function prototypes
*/

void	            init_v6(void);
void	            proc_v4(char *, ssize_t, struct msghdr *, struct timeval *);
void	            proc_v6(char *, ssize_t, struct msghdr *, struct timeval *);
void	            send_v4(void);
void	            send_v6(void);
void	            readloop(void);
void	            sig_alrm(int);
void	            tv_sub(struct timeval *, struct timeval *);

/*
** We use the proto structure to handle the difference between IPv4 and IPv6
** This structure contains two function pointers to socket address structures,
** the size of the socket address structures, and the protocol value of ICMP.
** the global pointer to one of the structures that we initialize for either
** IPv4 or IPv6
*/

struct proto {
    void	            (*fproc)(char *, ssize_t, struct msghdr *, struct timeval *);
    void                (*fsend)(void);
    void                (*finit)(void);
    struct sockaddr     *sasend;	    /* sockaddr{} for send, from getaddrinfo */
    struct sockaddr     *sarecv;	    /* sockaddr{} for receiving */
    socklen_t	        salen;		    /* length of sockaddr{}s */
    int	   	            icmpproto;	    /* IPPROTO_xxx value for ICMP */
} *pr;

#endif