/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:05:38 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/20 18:12:11 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

static void prompt_login(int check)
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

int comunicate_login(int sockid, char *buf)
{
	int res ;

	res = 0;
	write(sockid, buf, ft_strlen(buf));
	ft_bzero(buf, 128);
	read(sockid, buf, 128);
	write(1, buf, ft_strlen(buf));
	return (res);
}

int my_read(int buffsize, int fd, int block,\
			int (*fct)(int, char *), int sock)
{
	char buf[buffsize];
	int cmp;
	int r;
	int ret;

	ret = 0;
	r = 0;
	cmp = 0;
	ft_bzero(buf, buffsize);
	while (r == (buffsize - 1) || r <= 0)
	{
		r = read(fd, buf, buffsize-1);
		if (r == 0)
			exit_error("Bye, have a beautifull day !");
		if (r == 1 && cmp == 0)
			return (-2);
		buf[r] = '\0';
		cmp++;
		if (cmp == 1 && block == 1)
		{
			fct(sock, buf);
			ret = ft_strsearch(buf, "SUCCESS\n");
		}
		ft_bzero(buf, buffsize);
	}
	return (ret);
}
int login(t_env *e)
{
	int r;
	char buf[128];
	int user;
	int (*com_log)(int, char *);
	int i;

	i = 0;
	user = 0;
	com_log = comunicate_login;
	ft_bzero(buf,128);
	r = 0;
	write(1,"USER:\n",6);
	write(1,"\x1B[32mftp> \x1B[0m",14);
	while (1)
	{
		if (r == 1 && user == 1)
			break;
		r = my_read(128, 0, 1, com_log, SK);
		if (r == -2)
			;
		else if (r < 0)
			return (-1);
		else if (r == 1 && user == 0)
		{
			user = 1;
			r = 0;
		}
		if (r != 1 || user != 1)
			prompt_login(user);	
	}
		r = 0;
		ft_bzero(buf,128);
	return (0);
}
