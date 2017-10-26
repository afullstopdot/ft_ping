/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 08:48:44 by amarquez          #+#    #+#             */
/*   Updated: 2016/12/19 14:29:45 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel(char **as)
{
	if (*as)
		free(*as);
	*as = NULL;
}
