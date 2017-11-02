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
# include <sys/time.h>
# include <netinet/in_systm.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <errno.h>

/*
** We include two headers that define the IPv6 and ICMPv6 structures and constants
*/

#ifdef IPV6
    # include <netinet/ip6.h>
    # include <netinet/icmp6.h>
    # define IS_IPV6 1
#endif

/*
** TRUE / FALSE constants
*/

# define TRUE 1
# define FALSE 0

/*
** Default BUFFSIZE
*/

# define BUFSIZE 1500

/*
** Handled options
*/

# define A_VERBOSE "-v"
# define A_SWEEPINCRSIZE "-h"

/*
** Colors
*/

# define C_RED "\x1B[31m"
# define C_GRN "\x1B[32m"
# define C_YEL "\x1B[33m"
# define C_BLU "\x1B[34m"
# define C_MAG "\x1B[35m"
# define C_CYN "\x1B[36m"
# define C_WHT "\x1B[37m"
# define C_RST "\x1B[0m"

/*
** ROOT UID value
*/

# define ROOT_UID 0

/*
** program options, currently - [v, h] are handled
*/

typedef struct      s_env
{
    
    /*
    ** Verbose output
    */
    
    unsigned int    verbose;

    /*
    ** Specify the number of bytes to increment the size of the ICMP payload
    ** after each sweep when sending sweeping pings. The default value is 1
    */

    unsigned int    sweepincrsize;

    /*
    ** Host to ping, can be DNS or IP address
    */

    char            *host;
}                   t_env;

/*
** t_proto structure is used to handle the difference between IPv4 and IPv6
*/

typedef struct      s_proto
{

    /*
    ** Process ICMPv4/6 message, pointer to a function so it can point to IPv4 or IPv6
    */

    void            (*fproc) (char *, ssize_t, struct msghdr *, struct timeval *);

    /*
    ** Build and send ICMP ECHO_REQUEST message
    */

    void            (*fsend) (void);

    /*
    ** Initialize [here]
    */

    void            (*finit) (void);

    /*
    ** sockaddr{} for sending, from getaddrinfo
    */

    struct sockaddr *sasend;

    /*
    ** sockaddr{} for receiving
    */

    struct sockaddr *sacrecv;

    /*
    ** length of sockaddr {}s
    */

    socklen_t       salen;

    /*
    ** IPPROTO_xx value for ICMP (IPv4/IPv6)
    */

    int             icmpproto;
}                   t_proto;

/*
** t_env, t_proto and some values that will be needed/updated globally
*/

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

/*
** Global variable
*/

extern t_global     *g_global;

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
void                readloop(void);
uint16_t            in_cksum(uint16_t *addr, int len);
void                ft_init_proto_ipv4(t_proto *proto_v4);

/*
** privilege functions
*/

void                ft_set_superuser(void);

/*
** Wrapper functions
*/

void                ft_gettimeofday(struct timeval *tv, void *foo);
void	            ft_sendto(int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen);
void                *ft_calloc(size_t n, size_t size);

/*
** Signals
*/

void                sig_alrm(int signo);

/*
** Wrappers
*/

struct addrinfo     *ft_host_serv(const char *host, const char *serv, int family, int socktype);

#endif