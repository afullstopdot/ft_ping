#include <ping.h>

/*
**
*/

void    readloop(void)
{

    int             size;
    char            recvbuf[BUFSIZE];
    char            controlbuf[BUFSIZE];
    struct msghdr   msg;
    struct iovec    iov;
    ssize_t         n;
    struct timeval  tval;

    if ((g_global->sockfd = socket(g_global->pr->sasend->sa_family, SOCK_RAW, g_global->pr->icmpproto)) < 0)
        ft_fatal_error("failed to connect raw socket");

    // setuid(getuid()); /* don't need special permissions any more */

    if (g_global->pr->finit)
        (*g_global->pr->finit) ();

    size = 60 * 1024; /* OK if setsockopt fails */
    setsockopt (g_global->sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof (size));
    sig_alrm (SIGALRM); /* send first packet */
    iov.iov_base = recvbuf;
    iov.iov_len = sizeof (recvbuf);
    msg.msg_name = g_global->pr->sacrecv;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = controlbuf;
    for ( ; ; ) {
        msg.msg_namelen = g_global->pr->salen;
        msg.msg_controllen = sizeof (controlbuf);
        n = recvmsg (g_global->sockfd, &msg, 0);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            else
                ft_fatal_error("recvmsg error");
        }
        ft_gettimeofday(&tval, NULL);
        (*g_global->pr->fproc) (recvbuf, n, &msg, &tval);
    }
    return ;
}