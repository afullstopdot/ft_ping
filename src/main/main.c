#include <ping.h>

/*
** Set global to NULL 
*/

t_global			*g_global = NULL;

/*
** Start of program
*/

int                 main(int argc, char **argv)
{

	/*
	** IPv4 {}
	*/

    t_proto         proto_v4;

    /*
    ** IPv6 {}
    */

    // t_proto         proto_v6;

    /*
    **
    */

	char			*host_addr;

	/*
	** Program environment
	*/

    t_env			*env;

    /*
    ** Host Address info
    */

    struct addrinfo	*host_addrinfo;

    /*
    ** Allocate some memory for 
    */

    if (!(env = (t_env *)malloc(sizeof(t_env))) ||
    	!(g_global = (t_global *)malloc(sizeof(t_global))))
    	ft_fatal_error("failed to dynamically allocate memory");

    /*
    ** Set the program begin time
    */

    gettimeofday(&env->tv_begin, NULL);

    /*
    ** Initialize proto_ipv4
    */

    ft_init_proto_ipv4(&proto_v4);
    
    /*
    ** initialize server options
    */
    
    if (init_env(argc, argv, env))
    {

        /*
        ** Try and connect to SU
        */

        ft_set_superuser();

        /*
        ** env, has the args passed
        */

		g_global->env = env;

        /*
        ** We set the amount of optional data that gets sent with the ICMP echo request to 56 bytes.
        ** This will yield an 84-byte IPv4 datagram (20-byte IPv4 header and 8-byte ICMP header)
        ** or a 104-byte IPv6 datagram. Any data that accompanies an echo request must be sent back in the echo reply.
        ** We will store the time at which we send an echo request in the first 8 bytes of this data area and then 
        ** use this to calculate and print the RTT when the echo reply is received.
        */

		g_global->datalen = 56;

        /*
        ** ICMP ID field is 16 bits
        */

		g_global->pid = getpid() & 0xffff;

        /*
        ** Add singal
        */

        signal(SIGALRM, sig_alrm);
        signal(SIGINT, sig_int);

        /*
        ** Process host, if successful.
        ** The addrinfo {} will be point to a linked list of host
        ** using the protocol family (IPv4/IPv6) we will set the global pr
        ** with the right proto (proto_v4/proto_v6)
        */

        host_addrinfo = ft_host_serv (g_global->env->host, NULL, 0, 0);

        /*
        ** Convert hostaddresses from binary to text form
        */

        host_addr = ft_sock_ntop_host(host_addrinfo->ai_addr, host_addrinfo->ai_addrlen);

        /*
        ** Convert IPv4/IPv6 addresses from binary to text form
        */

        printf("PING %s (%s): %d data bytes\n", host_addrinfo->ai_canonname ? host_addrinfo->ai_canonname : host_addr, host_addr, g_global->datalen);

        /*
        **
        */

        if (host_addrinfo->ai_family == AF_INET)
        {
        
            g_global->pr = &proto_v4;
        
        }
        else
            ft_fatal_error("unknown address family");
  
        /*
        **
        */
    
        g_global->pr->sasend = host_addrinfo->ai_addr;

        /*
        **
        */

        g_global->pr->sacrecv = ft_calloc (1, host_addrinfo->ai_addrlen);

        /*
        **
        */

        g_global->pr->salen = host_addrinfo->ai_addrlen;

        /*
        **
        */

        readloop();

    }
    else
        dump_usage();
    return (0);
}