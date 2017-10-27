#include	"ping.h"

static Sigfunc 	*signal(int signo, Sigfunc *func)
{
	struct sigaction	act;
	struct sigaction	oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
	} else {
#ifdef	SA_RESTART
		act.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}

/*
** Signal function wrapper
*/

Sigfunc 		*ft_wsignal(int signo, Sigfunc *func)
{
	Sigfunc	*sigfunc;

	/*
	** Call wrapper, handle return before passing back to main
	*/

	if ((sigfunc = signal(signo, func)) == SIG_ERR)
	{
		printf("Error set SIGARLM");
		exit(EXIT_SUCCESS);
	}
	return(sigfunc);
}
