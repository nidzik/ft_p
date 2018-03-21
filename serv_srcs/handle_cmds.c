/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 23:20:46 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/21 19:32:53 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int			handle_ls(char **cmd, t_env *e)
{
	int		status;
	int		i;
	char	*gg;

	gg = NULL;
	i = SK;
	status = 0;
	if (!cmd[1] || (!ft_strncmp(cmd[1], "/\0", 2)))
		gg = ".";
	if (gg || (cmd[1] && check_path(cmd[1], e->ref) != -1))
	{
		if (!gg)
			gg = cmd[1];
		core_ls(i, gg, &status);
		check_return_ls(status, SK);
	}
	else
		write(SK, "ls : no such file or directory.\nERROR\n\0", 39);
	return (0);
}

int			handle_cd(char *cmd, t_env *e)
{
	char	*cwd;
	char	**arrcmd;
	char	*gg;

	arrcmd = NULL;
	cwd = NULL;
	getcwd(cwd, MAXPATHLEN);
	arrcmd = create_tab(cmd);
	gg = NULL;
	if (!arrcmd[1] || (!ft_strncmp(arrcmd[1], "/\0", 2)))
		gg = ".";
	if (gg || (arrcmd[1] && check_path(arrcmd[1], e->ref) != -1))
	{
		if (!gg)
			gg = arrcmd[1];
		if (arrcmd[1] == NULL)
			return (error_cmd_cd(SK, cmd, "", NULL));
		check_ret_cd(SK, gg, arrcmd);
	}
	else
		error_cmd_cd(SK, "cd", "No such file or directory.\nERROR\n\0",\
					arrcmd[1]);
	return (0);
}

void		get_fct(char *cmd, t_env *e)
{
	char	**array_cmd;

	array_cmd = NULL;
	array_cmd = create_tab(cmd);
	if (ft_strncmp("ls\0", array_cmd[0], 3) == 0)
		handle_ls(array_cmd, e);
	else if (ft_strncmp("pwd", array_cmd[0], ft_strlen(array_cmd[0])) == 0)
		get_pwd(cmd, e);
	else if (ft_strncmp("cd", array_cmd[0], ft_strlen(array_cmd[0])) == 0)
		handle_cd(cmd, e);
	else if (ft_strncmp("get ", cmd, 4) == 0)
		handle_get(cmd, e);
	else if (ft_strncmp("put ", cmd, 4) == 0)
		handle_put(cmd, e);
	else if (ft_strequ("quit", cmd) == 1)
		handle_quit(cmd, e);
	else
		write(SK, "command not found\nERROR\n\0", 25);
}

void		get_pwd(char *buf, t_env *e)
{
	char	path[1024];

	ft_bzero(path, 1024);
	(void)buf;
	getcwd(path, sizeof(path));
	ft_putnbr((int)sizeof(path));
	ft_putendl(path);
	path[ft_strlen(path)] = '\n';
	path[ft_strlen(path) + 1] = '\0';
	write(SK, path, ft_strlen(path));
	write(SK, "SUCCESS\n\0", 9);
	write(1, path, ft_strlen(path));
	ft_bzero(path, 1024);
}
