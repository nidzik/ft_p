/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:10:38 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/23 19:19:16 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		core_put(int sk, t_file *f)
{
	if (ft_strsearch(f->buf, "ERROR\n\0"))
		write(sk, "put : no such file or directory.\nERROR\n\0", 40);
	else if (f->r < 0)
	{
		write(sk, "Socket disconected.\nERROR\n\0", 27);
		return (-42);
	}
	else if (f->r == 0)
	{
		write(f->file, "\0", 1);
		write(sk, "Uplodad completed.\nSUCCESS\n\0", 28);
		return (-42);
	}
	else if (f->r < BUFSIZE)
	{
		write(sk, "Uplodad completed.\nSUCCESS\n\0", 28);
		return (-42);
	}
	return (1);
}

int		core_get(int sk, t_file *f)
{
	if (f->r < 0)
	{
		ft_arraydel(f->arr);
		exit_error("Erorr reading buf");
	}
	write(sk, f->buf, f->r);
	ft_bzero(f->buf, BUFSIZE);
	if (f->r != BUFSIZE)
		return (-42);
	f->r = 0;
	return (1);
}
