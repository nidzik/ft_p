/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 20:34:59 by nidzik            #+#    #+#             */
/*   Updated: 2018/04/02 16:34:01 by nidzik           ###   ########.fr       */
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

void	handle_error_snd_rcve(int r, t_env *e)
{
	if (r == 0)
	{
		ft_putendl("Bye...");
		handle_quit(NULL, e);
	}
	else
		exit_error("Read error. Exit...");
}

void	init_snd_rcve(int *cmp, int *r)
{
	*cmp = 0;
	*r = 0;
	write(1, "\x1B[32mftp> \x1B[0m", 14);
}

int		core_put(int sk, t_file *f)
{
	if (f->r < 0)
		exit_error("Erorr reading f.buf");
	if (f->r == 0)
	{
		write(sk, "EMPTY\n\0", 7);
		return (-42);
	}
	write(sk, f->buf, f->r);
	ft_bzero(f->buf, BUFSIZE);
	if (f->r != BUFSIZE)
		return (-42);
	f->r = 0;
	return (1);
}

int		core_get(t_file *f)
{
	if (ft_strsearch(f->buf, "EMPTY\n"))
	{
		return (-42);
	}
	write(f->file, f->buf, f->r);
	ft_bzero(f->buf, BUFSIZE);
	if (f->r != BUFSIZE)
		return (-42);
	f->r = 0;
	return (1);
}
