#include "ping.h"

/*
** proc_v4 processes all recieved ICMPv4 messages
**
** NOTE:
** When the ICMPv4 message is recieved by the process on the raw socket
** the kernel has already verified that the basic fields in the IPv4 header
** and in the ICMPv4 header are valid
*/

void    proc_v4 (char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{

    int             hlenl;
    int             icmplen;
    double          rtt;  
    struct ip       *ip;  
    struct icmp     *icmp;  
    struct timeval  *tvsend;  

    // temp, not used 
    if (msg)
        ft_fatal_error("msg is NULL");

    /*
    ** Start of IP header
    */

    ip = (struct ip *) ptr;

    /*
    ** Length of IP header
    */

    hlenl = ip->ip_hl << 2;

    /*
    ** Check that IP header is ICMP
    */

    if (ip->ip_p != IPPROTO_ICMP)
        return ;
    
    /*
    ** Start of ICMP header
    */

    icmp = (struct icmp *) (ptr + hlenl);

    /*
    ** Check that not malformed packet
    */

    if ((icmplen = len - hlenl) < 8)
        return ;

    if (icmp->icmp_type == ICMP_ECHOREPLY)
    {

        /*
        ** Check that there is a response to our ECHO_REQUEST
        */

        if (icmp->icmp_id != g_global->pid)
            return ;

        /*
        ** Check that there is enough data to use
        */

        if (icmplen < 16)
            return;

        /*
        **
        */

        tvsend = (struct timeval *) icmp->icmp_data;

        /*
        ** Get timeval difference
        */

        ft_tv_subtract(tvrecv, tvsend);

        /*
        ** 
        */

        rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

        /*
        ** print rtt
        */

        printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n",
            icmplen, ft_sock_ntop_host(g_global->pr->sacrecv, g_global->pr->salen),
            icmp->icmp_seq, ip->ip_ttl, rtt);

    }
    else if (g_global->env->verbose)
    {

        printf(" %d bytes from %s: type = %d, code = %d\n",
            icmplen, ft_sock_ntop_host(g_global->pr->sacrecv, g_global->pr->salen),
            icmp->icmp_type, icmp->icmp_code);

    }

}