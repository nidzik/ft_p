/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 22:29:14 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/16 22:29:18 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char **cmd_to_split(char *cmd)
{
  char **array_cmd;

  array_cmd = NULL;
  array_cmd = ft_strsplit(cmd, ' ');
  return (array_cmd);
}

int check_path(char *path, char* path_ref)
{
	char old_path[MAXPATHLEN]=  {};
	char new_path[MAXPATHLEN] = {};

//	new_path = NULL;
//	old_path = NULL;
	getcwd(old_path, MAXPATHLEN);
	ft_putendl(path);
	if (chdir(path) < 0 )
	{
		ft_putendl("retdirt");
		return (-1);
	}
	getcwd(new_path, MAXPATHLEN);
	if (!ft_strncmp(new_path, path_ref, ft_strlen(path_ref) - 1))
	{
		ft_putendl("YES..");
		chdir(old_path);
		return (1);
	}
	else
	{
		ft_putendl(old_path);
		chdir(old_path);
		ft_putendl("NO..");
		return (-1);
	}
}
