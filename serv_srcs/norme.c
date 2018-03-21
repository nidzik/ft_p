/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:58:04 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/21 17:31:56 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void		check_return_ls(int status, int sock)
{
	if (status != 256)
		write(sock, "SUCCESS\n\0", 9);
	else
		write(sock, "ls : no such file or directory.\nERROR\n\0", 39);
}

void		core_ls(int i, char *arg, int *status)
{
	int				pid;
	struct rusage	usage;

	pid = 0;
	if ((pid = fork()) < 0)
		exit(0);
	else if (pid == 0)
	{
		if (i != -1 && i != 1)
			dup2(i, 1);
		execl("/bin/ls", "ls", "-la", arg, NULL);
		exit(0);
	}
	else
		wait4(pid, status, 0, &usage);
}

int			create_ref(t_env *e)
{
	char cwd[1024];

	ft_bzero(cwd, 1024);
	getcwd(cwd, sizeof(cwd));
	cwd[ft_strlen(cwd)] = '\n';
	cwd[ft_strlen(cwd) + 1] = '\0';
	e->ref = ft_strdup(cwd);
	return (1);
}

int			core_connect_pass(t_env *e, int sockid)
{
	int		r;
	char	pass[128];

	ft_bzero(pass, 128);
	r = 0;
	while (1)
		while ((r = read(sockid, (char *)pass, 128)) > 0)
		{
			if (r >= 0)
			{
				pass[r - 1] = '\0';
				if (check_pass(pass, sockid) != -1)
					return (create_ref(e));
			}
			if (r == -1)
			{
				write(sockid, "Cannot create user\nERROR\n\0", 26);
				exit_error("ERROR while readding the socket\n");
			}
			ft_bzero(pass, 128);
		}
	return (0);
}
