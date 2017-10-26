#include <ping.h>

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