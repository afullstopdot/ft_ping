#include "ping.h"

/*
** SIGALRM signal handler
*/

void    sig_alrm (int signo)
{

    /*
    **
    */

    (g_global->(*pr)->fsend) ();

    /*
    **
    */

    alarm(1);

    /*
    **
    */

    return ;

}