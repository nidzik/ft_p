/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 22:29:14 by nidzik            #+#    #+#             */
/*   Updated: 2018/04/01 19:45:07 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char		**cmd_to_split(char *cmd)
{
	char		**array_cmd;

	array_cmd = NULL;
	array_cmd = ft_strsplit(cmd, ' ');
	return (array_cmd);
}

int			check_path(char *path, char *path_ref)
{
	char	old_path[MAXPATHLEN];
	char	new_path[MAXPATHLEN];

	ft_bzero(old_path, sizeof(old_path));
	ft_bzero(new_path, sizeof(new_path));
	getcwd(old_path, MAXPATHLEN);
	if (chdir(path) < 0)
		return (-1);
	getcwd(new_path, MAXPATHLEN);
	if (!ft_strncmp(new_path, path_ref, ft_strlen(path_ref) - 1))
	{
		chdir(old_path);
		return (1);
	}
	else
	{
		chdir(old_path);
		return (-1);
	}
}

void		check_ret_cd(int sk, char *name, char **arr)
{
	if (chdir(name) < 0)
	{
		error_cmd_cd(sk, "cd", "No such file or directory.\nERROR\n\0",\
					arr[1]);
	}
	else
		write(sk, "SUCCESS\n\0", 9);
}
