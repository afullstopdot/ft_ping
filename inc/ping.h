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
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <netinet/in_systm.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
#ifdef IPV6
    # include <netinet/ip6.h>
    # include <netinet/icmp6.h>
    # define IS_IPV6 1
#endif

/*
** definitions
*/

# define TRUE 1
# define FALSE 0
# define BUFSIZE 1500
# define A_VERBOSE "-v"
# define A_SWEEPINCRSIZE "-h"
# define C_RED "\x1B[31m"
# define C_GRN "\x1B[32m"
# define C_YEL "\x1B[33m"
# define C_BLU "\x1B[34m"
# define C_MAG "\x1B[35m"
# define C_CYN "\x1B[36m"
# define C_WHT "\x1B[37m"
# define C_RST "\x1B[0m"
# define ROOT_UID 0

/*
** Runtime options
*/

typedef struct      s_env
{
    unsigned int    verbose;
    unsigned int    sweepincrsize;
    char            *host;
}                   t_env;

typedef struct      s_proto
{
    void            (*fproc) (char *, ssize_t, struct msghdr *, struct timeval *);
    void            (*fsend) (void);
    void            (*finit) (void);
    struct sockaddr *sasend;
    struct sockaddr *sarecv;
    socklen_t       salen;
    int             icmpproto;
}                   t_proto;

typedef struct      s_global
{
    int             sockfd;
    int             nsent;
    int             datalen;
    pid_t           pid;
    char            sendbuf[BUFSIZE];
    t_env           *env;
    t_proto         *pr;
}                   t_global;

extern t_global        *g_global;

/*
** interpreter functions
*/

int                 init_env(int argc, char **argv, t_env *env);

/*
** error funcions
*/

void                dump_usage(void);
void                ft_fatal_error(char *msg);


/*
** Socket functions
*/

void                ft_set_raw_socket(void);
char                *ft_sock_ntop_host(const struct sockaddr *sa, socklen_t salen);
void                ft_tv_subtract(struct timeval *out, struct timeval *in);

/*
** ICMP functions
*/

void                proc_v4 (char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv);
void                send_v4(void);
void                init_v6(void);

/*
** privilege functions
*/

void                ft_set_superuser(void);

/*
** Wrapper functions
*/

void                ft_gettimeofday(struct timeval *tv, void *foo);
void                *ft_calloc(size_t n, size_t size);

#endif