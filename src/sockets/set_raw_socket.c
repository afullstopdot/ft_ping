#include <ping.h>

/*
** This function must create a raw socket, and return the descriptor
*/

void    ft_set_raw_socket(t_global *global)
{

    int on;
    

    /*
    ** Check that struct is valid
    */

    on = 1;
    if (global)
    {

        /*
        ** Set program to superuser, will exit if fail
        */

        ft_set_superuser();

        /*
        ** The protocol is the constant definded in <netinet/in.h>
        ** Only the superuser can create a raw socket. This prevents normal users
        ** from writing their own IP datagrams to the network
        */

        if ((global->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
            ft_fatal_error("failed to connect raw socket");

        /*
        ** Set socket header options
        */

        if (setsockopt(global->sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
            ft_fatal_error("failed to set socket options");
    
    }

}