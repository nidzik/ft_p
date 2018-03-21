/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 21:27:11 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/21 18:48:49 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

int		handle_rest(char *cmd, t_env *e)
{
	int		r;
	char	buf[BUFSIZE];
	int		i;

	i = 0;
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	ft_bzero(buf, BUFSIZE);
	r = 0;
	while ((r = read(e->socketid, buf, BUFSIZE)) > 0)
	{
		if (r <= 0)
			exit_error("Erorr reading buf");
		while (i < BUFSIZE)
			ft_putchar(buf[i++]);
		i = 0;
		if (ft_strsearch(buf, "ERROR\n") || ft_strsearch(buf, "SUCCESS"))
		{
			ft_bzero(buf, BUFSIZE);
			return (-1);
		}
		ft_bzero(buf, BUFSIZE);
	}
	return (1);
}

void	handle_quit(char *cmd, t_env *e)
{
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	free(e);
	exit(0);
}
