#include <ping.h>

static int          get_verbose(char **argv)
{

    int             count;

    count = 1;
    while (argv[count])
    {

        if (ft_strequ(argv[count], A_VERBOSE))
            return (TRUE);
        count++;

    }
    return (FALSE);

}

/*
** sweepincrsize Specify the number of bytes to increment the size of ICMP payload
** after each sweep when sending sweeping pings. The default value is 1.
*/

static  int         get_sweepincrsize(char **argv)
{

    int             count;
    
        count = 1;
        while (argv[count])
        {
    
            if (ft_strequ(argv[count], A_SWEEPINCRSIZE))
            {

                if (argv[count + 1])
                {

                    return (ft_atoi(argv[count + 1]));

                }

            }
            count++;
    
        }

        /*
        ** Default value is 1
        */

        return (1);    

}

static  char        *get_host(char **argv)
{

    int             count;
    
    count = 1;
    while (argv[count])
    {

        if (!ft_strchr(argv[count], '-'))
        {

            return (ft_strdup(argv[count]));

        }
        count++;

    }
    return (NULL);    

}

/*
** Initialize ping environment
*/

int                 init_env(int argc, char **argv, t_env *env)
{

    unsigned int    verbose;
    unsigned int    sweepincrsize;
    char            *host;

    verbose = get_verbose(argv);
    sweepincrsize = get_sweepincrsize(argv);
    host = get_host(argv);
    if (argc < 2 || !host)
        return (FALSE);

    /*
    ** Set env to default
    */

    env->verbose = verbose;
    env->sweepincrsize = sweepincrsize;
    env->host = host;

    /*
    ** If we got this far, everything worked out
    */

    return (TRUE);

}