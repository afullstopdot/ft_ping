#include <ping.h>

/*
** Initialize proto struct for IPv4
*/

void	ft_init_proto_ipv4(t_proto *proto_v4)
{

	/*
	** Process ICMPv4 ECHO_REPLY message, points to proc_v4 defined for IPv4
	*/

	proto_v4->fproc = proc_v4;

	/*
	** Build and Send ICMPV4 ECHO_REQUEST message,
	*/

    proto_v4->fsend = send_v4;

    /*
    ** Initialize, this is for IPv6 so is set to NULL
    */

    proto_v4->finit = NULL;

    /*
    ** sockaddr {} for sending ECHO request, will be updated after
    ** raw socket is created.
    */

    proto_v4->sasend = NULL;

    /*
    ** sockaddr {} for sending ECHO request, will be updated after
    ** raw socket is created.
    */

    proto_v4->sacrecv = NULL;

    /*
    ** sockaddr {} for recieving ECHO reply
    */

    proto_v4->salen = 0;

    /*
    ** IPPROTO_xx value for ICMP, Set for IPv4
    */

    proto_v4->icmpproto = IPPROTO_ICMP;

}