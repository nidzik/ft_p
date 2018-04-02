/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:10:38 by nidzik            #+#    #+#             */
/*   Updated: 2018/04/02 16:49:34 by nidzik           ###   ########.fr       */
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
		write(sk, "Upload completed.\nSUCCESS\n\0", 27);
		return (-42);
	}
	else if (f->r < BUFSIZE)
	{
		write(sk, "Upload completed.\nSUCCESS\n\0", 27);
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

void	handler(int sig)
{
	pid_t			pid;
	struct rusage	u;

	(void)sig;
	pid = wait4(-1, 0, 0, &u);
}

int		core_accept(t_env *elp)
{
	t_env	*e;
	int		i;

	e = elp;
	i = 0;
	signal(SIGCHLD, handler);
	if ((e->pid = fork()) == 0)
	{
		close(e->socketid);
		if (connect_me(e->accept_socket, e) != -42)
			ft_ftp(e);
		close(e->accept_socket);
		free(e);
		exit(0);
	}
	else if (e->pid > 0)
	{
		close(elp->accept_socket);
	}
	return (0);
}
