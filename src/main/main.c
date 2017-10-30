#include <ping.h>

int         main(int argc, char **argv)
{
    t_env           *env;
    t_global        *global;

    /*
    ** ping environment
    */

    if (!(env = (t_env *)malloc(sizeof(t_env))) || !(global = (t_global *)malloc(sizeof(t_global))))
        return (0);
    
    /*
    ** initialize server options
    */
    
    if (init_env(argc, argv, env))
    {

        /*
        ** Add env to global struct, set default datalen
        */

        global->env = env;
        global->datalen = 56;

        /*
        ** Set socket, set sockfd in global
        */

        ft_set_raw_socket(global);

    }
    else
        dump_usage();
    return (0);
}