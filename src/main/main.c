#include <ping.h>

struct proto	proto_v4 = { proc_v4, send_v4, NULL, NULL, NULL, 0, IPPROTO_ICMP };

#ifdef	IPV6
    struct proto	proto_v6 = { proc_v6, send_v6, init_v6, NULL, NULL, 0, IPPROTO_ICMPV6 };
#endif

/*
** Data that goes with ICMP echo request
**
** We set the amount of optional data that gets sent with the ICMP echo request to 56 bytes.
** this will yield an 84 byte IPv4 datagram (20-byte IPv4 header and 8-byte ICMP header)
** or a 104-byte IPv6 datagram. Any data that accompanies an echo request must be
** sent back in the echo reply.
*/

int	datalen = 56;

/*
** Server main
*/

int         main(int argc, char **argv)
{
    t_env           *env;
    struct addrinfo	*ai;
	char            *h;

    /*
    ** ping environment
    */
    
    if (!(env = (t_env *)malloc(sizeof(t_env))))
        return (0);
    
    /*
    ** initialize server options
    */
    
    if (init_env(argc, argv, env))
    {
 
        /*
        ** ICMP ID field is 16 bits
        */

        pid = getpid() & 0xffff;

        /*
        ** Set sigalarm
        */

        ft_wignal(SIGALRM, sig_alrm);

        /*
        ** Set host address informaion
        */

        ai = ft_whost_serv(host, NULL, 0, 0);

        /*
        ** Convert IPv4/IPv6 addresse from text to binary form
        */

        h = ft_wsock_ntop_host(ai->ai_addr, ai->ai_addrlen);

        /*
        ** Display current ping settings that will be used
        */

        printf("PING %s (%s): %d data bytes\n", ai->ai_canonname ? ai->ai_canonname : h, h, datalen);

        /*
        ** 4initialize according to protocol
        */

        if (ai->ai_family == AF_INET) {
            pr = &proto_v4;
#ifdef	IPV6
        }
        else if (ai->ai_family == AF_INET6) {
            pr = &proto_v6;
            if (IN6_IS_ADDR_V4MAPPED(&(((struct sockaddr_in6 *)ai->ai_addr)->sin6_addr)))
            {
                printf("cannot ping IPv4-mapped IPv6 address");
                exit(EXIT_SUCCESS);
            }
#endif
        }
        else
        {
            printf("unknown address family %d", ai->ai_family);
            exit(EXIT_SUCCESS);
        }

        pr->sasend = ai->ai_addr;
        pr->sarecv = calloc(1, ai->ai_addrlen); //use temp for now. will create a wrapper later
        pr->salen = ai->ai_addrlen;

        /*
        ** readloop is where the processing takes place
        */

        readloop();
    
    }
    else
        dump_usage();
    return (0);
}