/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 15:11:14 by amarquez          #+#    #+#             */
/*   Updated: 2017/07/11 15:12:08 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
# define PING_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <libft.h>
# include <netinet/in_systm.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>

/*
** definitions
*/

# define TRUE 1
# define FALSE 0
# define BUFSIZE 1500
# define A_VERBOSE "-v"
# define A_SWEEPINCRSIZE "-h"

/*
** Runtime options
*/

typedef struct      s_env
{
    unsigned int    verbose;
    unsigned int    sweepincrsize;
    char            *host;
}                   t_env;

/*
** interpreter functions
*/

int     init_env(int argc, char **argv, t_env *env);

/*
** error funcions
*/

void    dump_usage(void);

#endif