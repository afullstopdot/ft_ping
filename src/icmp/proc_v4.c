#include "ping.h"

/*
** proc_v4 processes all recieved ICMPv4 messages
**
** NOTE:
** When the ICMPv4 message is recieved by the process on the raw socket
** the kernel has already verified that the basic fields in the IPv4 header
** and in the ICMPv4 header are valid
*/

void    proc_v4 (char *ptr, ssize_t len, struct msghhdr *msg, struct timeval *tvrecv)
{

    int             hlenl;
    int             icmplen;
    double          rtt;  
    struct ip       *ip;  
    struct icmp     *icmp;  
    struct timeval  *tvsend;  

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

        if (icmp->icmp_id != pid)
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

        tv_sub(tvrecv, tvsend);

        /*
        ** 
        */

        rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

        /*
        ** print rtt
        */

        printf(" %d bytes from %s: type = %d, code = %d\n",
            icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
            icmp->icmp_type, icmp->icmp_code);

    }
    else if (verbose)
    {

        printf(" %d bytes from %s: type = %d, code = %d\n",
            icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
            icmp->icmp_type, icmp->icmp->icmp_code);

    }

}