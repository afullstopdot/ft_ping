#include <ping.h>

t_global    *g_global = NULL;

int         main(int argc, char **argv)
{
    t_proto             proto_v4;
    char                *h;
    t_env               *env;
    struct addrinfo     *ai;
    // t_proto         proto_v6;

    proto_v4.fproc = proc_v4;
    proto_v4.fsend = send_v4;
    proto_v4.finit = NULL;
    proto_v4.sasend = NULL;
    proto_v4.sacrecv = NULL;
    proto_v4.salen = 0;
    proto_v4.icmpproto = IPPROTO_ICMP;
    if (!(env = (t_env *)malloc(sizeof(t_env))) || !(g_global = (t_global *)malloc(sizeof(t_global))))
        return (0);
    
    /*
    ** initialize server options
    */
    
    if (init_env(argc, argv, env))
    {

        /*
        ** Add env to global struct, set default datalen
        */

        g_global->env = env;
        g_global->datalen = 56;
        g_global->pid = getpid() & 0xffff;

        /*
        ** 
        */

        signal(SIGALRM, sig_alrm);

        /*
        **
        */

        ai = ft_host_serv (g_global->env->host, NULL, 0, 0);

        /*
        **
        */

        h = ft_sock_ntop_host(ai->ai_addr, ai->ai_addrlen);

        /*
        **
        */

        printf ("PING %s (%s): %d data bytes\n", 
            ai->ai_canonname ? ai->ai_canonname : h, h, g_global->datalen);

        /*
        **
        */

        if (ai->ai_family == AF_INET)
        {
        
            g_global->pr = &proto_v4;
        
        }
        else
            ft_fatal_error("uknown address family");
  
        /*
        **
        */
    
        g_global->pr->sasend = ai->ai_addr;

        /*
        **
        */

        g_global->pr->sacrecv = ft_calloc (1, ai->ai_addrlen);

        /*
        **
        */

        g_global->pr->salen = ai->ai_addrlen;

        /*
        **
        */

        readloop();

    }
    else
        dump_usage();
    return (0);
}