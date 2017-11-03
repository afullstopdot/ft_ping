#include <ping.h>

/*
** Processing takes place here
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

    /*
    ** Connect to host
    */

    if ((g_global->sockfd = socket(g_global->pr->sasend->sa_family, SOCK_RAW, g_global->pr->icmpproto)) < 0)
        ft_fatal_error("failed to connect raw socket");

    /*
    ** Will have IPv6 support later, if finit is not null will initialize IPv6
    */

    if (g_global->pr->finit)
        (*g_global->pr->finit) ();

    /*
    ** I try to set the socket recieve buffer size to 61, 440 bytes (60 x 1024)
    ** which should be larger than the default. I do this incase the uuser pings either
    ** the IPv4 broadcast address or a multicast address, either of which can generate
    ** lots of replies. By making the buffer larger there is a smaller chance of a buffer ovrflow
    */

    size = 60 * 1024;
    
    /*
    ** OK if setsockopt fails
    */
    
    setsockopt (g_global->sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof (size));
    
    /*
    ** Send the first packet
    ** We call our signal handler which will send a packet and schedule a SIGALARN
    ** 1 second in the future
    */

    sig_alrm (SIGALRM);

    /*
    ** Set up the unchanging fields in the msghdr and iovec structs that we will pass to recvmsg
    */

    iov.iov_base = recvbuf;
    iov.iov_len = sizeof (recvbuf);
    msg.msg_name = g_global->pr->sacrecv;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = controlbuf;

    /*
    ** Main loop of the program, the infinite loop
    ** that reads all packets returned on the raw ICMP socket
    */

    while (42)
    {

        /*
        ** Set chaning fields
        */

        msg.msg_namelen = g_global->pr->salen;
        msg.msg_controllen = sizeof (controlbuf);

        /*
        ** Read packets
        */

        if ((n = recvmsg (g_global->sockfd, &msg, 0)) < 0)
            ft_fatal_error("recvmsg error");
        
        /*
        ** Get time the packet was recvd to calculate rtt later
        */

        ft_gettimeofday(&tval, NULL);

        /*
        ** Call the right function to handle the processing of the packet
        ** This is for later when i will handle IPv6
        */

        (*g_global->pr->fproc) (recvbuf, n, &msg, &tval);

    }
    return ;
}