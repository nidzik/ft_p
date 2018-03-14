/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:33:26 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/14 23:15:19 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int create_user(char *username)
{
	ft_putendl("AHAHAHAHAH");
	ft_putendl(username);
	return(mkdir(username, 0644));
}

int check_ifdirexist(char *path)
{
	struct stat sta;
	int fd;

	fd = open(path, O_RDONLY);
	return (fstat(fd ,&sta));
}

int check_username(char *user)
{
	return (check_ifdirexist(user));
}

void check_pass(void)
{
	;
}

int		connect_me(int sockid)
{
	char username[128];
	char pass[128];
	int r;

	r = 0;
	ft_bzero(username, 128);
	ft_bzero(pass, 128);
	while ((r = read(sockid, (char *)username, 128)) > 0)
	{
		if (r == -1)
			exit_error("ERROR while readding the socket\n");
		username[r-1] = '\0';
		if (check_username(username) != -1)
		{
			if (read(sockid, (char *)pass, 128) < 0)
				check_pass();
			else
				exit_error("ERROR while readding the socket\n");
		}
		else
		{
			if (create_user(username) == -1)
				exit_error("ERROR cannot create user.\n");
		}
		if (r == -1)
		break;
	}
	return (0);
}
