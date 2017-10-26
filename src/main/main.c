#include <ping.h>

struct proto proto_v4 = { proc_v4, send_v4, NULL, NULL, NULL, 0, IPPROTO_ICMP };

#ifdef IPV6
    struct proto proto_v6 = { proc_v6, send_v6, NULL, NULL, 0, IPPROTO_ICMPV6 };
#endif

int datalen = 56; /* data that goes with ICMP echo request */

/*
** Server main
*/

int         main(int argc, char **argv)
{
    t_env           *env;

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
 
        // do cool stuff here
    
    }
    else
        dump_usage();
    return (0);
}