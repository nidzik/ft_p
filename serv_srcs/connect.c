/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:33:26 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/19 19:06:10 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <mach/error.h>
int create_user(char *username)
{
	int i;
	i = mkdir(username, 0700);
	return(i);
}

int check_ifdirexist(char *path)
{
	struct stat sta;
	int i; 

	i = stat(path ,&sta);
	if (i < 0)
		printf("--error fd stat %s--\n",path);
	return (i);
}

int check_username(char *username, int sockid)
{
	int res;

	res = 0;
	if ((res = check_ifdirexist(username)) < 0)
	{
		if (create_user(username) == -1)
		{
			write(sockid, "Cannot create user\nERROR\n\0", 26);
			return (-1);
		}
		else
		{
			res = chdir(username);
			if (res == -1)
			{
				ft_putendl("eroro chdir");
				return (-1);
			}
		}
	}
	else 
		return (chdir(username));
	return (res);
}

int check_pass(char *pass, int sockid)
{
	if (check_ifdirexist(".pass") < 0)
	{
		return (create_pass(pass, sockid));
	}
	else
	{
		return (verify_pass(pass, sockid));
	}
}

int		connect_me(int sockid, t_env *e)
{
	char username[128];
	char pass[128];
	int r;
	char cwd[1024];
	r = 0;
	ft_bzero(username, 128);
	ft_bzero(pass, 128);
	while (1)
	{
	if ((r = read(sockid, (char *)username, 128)) > 0)
	{
		ft_putnbr(r);
		if (r == -1)
			exit_error("ERROR while readding the socket\n");
		username[r-1] = '\0';
		if (check_username(username, sockid) != -1)
		{
			ft_putendl("print here username");
			write(sockid, "Username set. Need password.\nSUCCESS\n\0", 38);
			while ((r = read(sockid, (char *)pass, 128)) > 0)
			{
				if (r >= 0)
				{
					pass[r-1] = '\0';
					if (check_pass(pass, sockid) != -1)
					{

						ft_bzero(cwd, 1024);
						getcwd(cwd, sizeof(cwd));
						cwd[ft_strlen(cwd)] = '\n';
						cwd[ft_strlen(cwd) + 1] = '\0';
						e->ref = ft_strdup(cwd);
						return (0);
					}
				}
				if (r == -1)
				{
					write(sockid, "Cannot create user\nERROR\n\0", 26);
//					return (-1);
					exit_error("ERROR while readding the socket\n");
				}
			}
		}
		else
			write(sockid, "Cannot connect to user.\nERROR\n\0" ,31);
	}
	}
	return (0);
}
