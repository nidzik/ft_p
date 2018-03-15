/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:05:38 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/15 22:40:52 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

static void prompt_login(int check)
{
	if (check == 1)
	{
		write(1,"PASSWORD:\n",10);
		write(1,"\x1B[32mftp> \x1B[0m",14);
	}
	else
	{
		write(1,"USER:\n",6);
		write(1,"\x1B[32mftp> \x1B[0m",14);
	}
}

static int comunicate_login(int sockid, char *buf)
{
	int res ;

	res = 0;
	write(sockid, buf, ft_strlen(buf));
	ft_bzero(buf, BUFSIZE);
	read(sockid, buf, BUFSIZE);
	write(1, buf, BUFSIZE);
	return (res);
}

static int create_refpath(char *buf, t_env *e)
{
	read(SK, buf, BUFSIZE);
	e->ref_path = ft_strdup(buf);
	return (1);
}

int login(t_env *e)
{
	int r;
	char buf[BUFSIZE];
	int user;

	user = 0;
	ft_bzero(buf,BUFSIZE);
	r = 0;
	write(1,"USER:\n",6);
	write(1,"\x1B[32mftp> \x1B[0m",14);
	while ((r = read(0, buf, BUFSIZE)) > 0)
	{
		buf[r] = '\0';
		if (ft_strlen(buf) > 1)
		{
			comunicate_login(e->socketid, buf);
			if (user == 0 && ft_strsearch(buf, "SUCCESS\n"))
				user = 1;
			else if (user == 1 && ft_strsearch(buf, "SUCCESS\n"))
				return (create_refpath(buf, e));
		}
		r = 0;
		ft_bzero(buf,BUFSIZE);
		prompt_login(user);
	}
	return (0);
}
