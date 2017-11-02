#include <ping.h>

/*
** Builds an ICMPv4 echo request message and sends it
*/

void                send_v4(void)
{

    int             len;
    struct icmp     *icmp;

    /*
    **
    */

    icmp = (struct icmp *) g_global->sendbuf;

    /*
    **
    */

    icmp->icmp_type = ICMP_ECHO;

    /*
    **
    */

    icmp->icmp_code = 0;

    /*
    **
    */

    icmp->icmp_id = g_global->pid;

    /*
    **
    */

    icmp->icmp_seq = g_global->nsent++;

    /*
    ** fill with pattern
    */

    memset (icmp->icmp_data, 0xa5, g_global->datalen);

    /*
    **
    */

    ft_gettimeofday ((struct timeval *) icmp->icmp_data, NULL);

    /*
    ** checksum ICMP header and data
    */

    len = 8 + g_global->datalen;

    /*
    **
    */

    icmp->icmp_cksum = 0;

    /*
    **
    */

    icmp->icmp_cksum = in_cksum ((u_short *) icmp, len);

    /*
    **
    */

    ft_sendto (g_global->sockfd, g_global->sendbuf, len, 0, g_global->pr->sasend, g_global->pr->salen);

}