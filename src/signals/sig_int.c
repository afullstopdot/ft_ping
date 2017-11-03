#include <ping.h>

/*
** SIGINT signal handler
*/

void                sig_int(int signo)
{

    /*
    ** number packets lostt
    */

    int             diff;

    /*
    ** percentage of loss
    */

    double          loss;

    /*
    ** Operation finish time
    */

    struct timeval  tv_end;

    /*
    ** finish in millieseconds
    */

    double          finish;

    /*
    ** default
    */

    loss = 0;
    diff = 0;
    finish = 0;

    /*
    ** Set end time
    */

    gettimeofday(&tv_end, NULL);

    /*
    ** Silence compiler
    */

    if (signo != SIGINT)
        return ;

    /*
    ** Loss count
    */

    diff = g_global->nsent - g_global->nrec;

    /*
    ** Claculate percentage
    */

    loss = (double) diff / g_global->nsent * 100;

    /*
    ** Get timeval difference
    */

    ft_tv_subtract(&tv_end, &g_global->env->tv_begin);

    /*
    ** Calculate the time value in milleseconds 
    */

    finish = tv_end.tv_sec * 1000.0 + tv_end.tv_usec / 1000.0;

    /*
    ** Dump final stats
    */

    printf("\n--- %s ping statistics ---\n%d packets transmitted, %d recieved, %.0f%% packet loss, time %.fms\n",
        g_global->env->host, g_global->nsent, g_global->nrec, loss, finish);
    printf("rtt min/max = %.3f/%.3f\n", g_global->rtts.min, g_global->rtts.max);

    /*
    ** Exit program
    */

    exit(EXIT_SUCCESS);

}