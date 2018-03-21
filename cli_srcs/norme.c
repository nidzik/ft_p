/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 20:34:59 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/21 19:44:51 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

int		snd_rcve_cmd(int *cmp, char *buf, t_env *e, int r)
{
	*cmp = *cmp + 1;
	if (*cmp == 1)
	{
		buf[r] = '\0';
		if (ft_strlen(buf) > 1)
			check_cmd(buf, e);
	}
	return (0);
}

void	handle_error_snd_rcve(int r)
{
	if (r == 0)
		exit_error("Bye...");
	else
		exit_error("Read error. Exit...");
}

void	init_snd_rcve(int *cmp, int *r)
{
	*cmp = 0;
	*r = 0;
	write(1, "\x1B[32mftp> \x1B[0m", 14);
}
