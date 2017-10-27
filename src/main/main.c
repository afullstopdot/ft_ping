#include <ping.h>

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
 
        
        // code dope shit here

    }
    else
        dump_usage();
    return (0);
}