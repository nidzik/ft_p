/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:05:38 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/23 19:01:52 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

static void	prompt_login(int check)
{
	if (check == 1)
	{
		write(1, "PASSWORD:\n", 10);
		write(1, "\x1B[32mftp> \x1B[0m", 14);
	}
	else
	{
		write(1, "USER:\n", 6);
		write(1, "\x1B[32mftp> \x1B[0m", 14);
	}
}

int			comunicate_login(int sockid, char *buf)
{
	int res;

	res = 0;
	write(sockid, buf, ft_strlen(buf));
	ft_bzero(buf, 128);
	read(sockid, buf, 128);
	write(1, buf, ft_strlen(buf));
	return (res);
}

int			my_read(int buffsize, int fd, int (*fct)(int, char *), int sock)
{
	char	buf[buffsize];
	int		cmp;
	int		r;
	int		ret;

	zeroo(&ret, &r, &cmp);
	ft_bzero(buf, buffsize);
	while (r == (buffsize - 1) || r <= 0)
	{
		r = read(fd, buf, buffsize - 1);
		if (r == 0)
			exit_error("Bye, have a beautifull day !");
		if (r == 1 && cmp == 0)
			return (-2);
		buf[r] = '\0';
		cmp++;
		if (cmp == 1)
		{
			fct(sock, buf);
			ret = ft_strsearch(buf, "SUCCESS\n");
		}
		ft_bzero(buf, buffsize);
	}
	return (ret);
}

void		init_login(t_file *f)
{
	f->r = 0;
	f->file = 0;
	f->cmp = 0;
	f->arr = NULL;
	f->namefile = NULL;
	write(1, "USER:\n", 6);
	write(1, "\x1B[32mftp> \x1B[0m", 14);
}

int			login(t_env *e)
{
	char	buf[128];
	t_file	f;

	init_login(&f);
	ft_bzero(buf, 128);
	while (1)
	{
		if (f.r == 1 && f.cmp == 1)
			break ;
		f.r = my_read(128, 0, comunicate_login, SK);
		if (f.r == -1)
			return (-1);
		else if (f.r == 1 && f.cmp == 0)
			uno(&f);
		if (f.r != 1 || f.cmp != 1)
			prompt_login(f.cmp);
	}
	f.r = 0;
	ft_bzero(buf, 128);
	return (0);
}
