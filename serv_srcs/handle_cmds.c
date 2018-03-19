/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 23:20:46 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/19 20:58:18 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int			handle_ls(char **cmd, t_env *e)
{
	int					pid;
	int					status;
	struct rusage   usage;
	int					i;
	int stdio[3];
	char *gg;
	int ret_fork; 

	ret_fork = 0;
	gg = NULL;
	if (!cmd[1] || (!ft_strncmp(cmd[1], "/\0", 2)))
		gg = ".";
	if (gg || (cmd[1] && check_path(cmd[1], e->ref) != -1))
	{
		if (!gg)
		gg = cmd[1];
//		gg = malloc(sizeof(char) * ft_strlen(ref) + ft_strlen(cmd[1]) * sizeof(char));
		//	gg = ft_strncpy(gg, ref, ft_strlen(ref));
		//gg = ft_strncat(gg, cmd[1], ft_strlen(cmd[1]));

//	printf("cmd1 = %s, gg = %s\n",cmd[1] , gg);fflush(stdout);
	stdio[1] = SK;
	stdio[2] = SK;
//	ft_print_array(cmd);
	if ((pid = fork()) < 0)
		exit (0);
	else if (pid == 0)
		{
			i = -1;
			while (++i < 2)
				if (stdio[i] != -1 && stdio[i] != i)
					dup2(stdio[i], i);
			ret_fork = execl("/bin/ls","ls","-la", gg, NULL);
			exit(1);
		}
	else
		wait4(pid, &status, 0, &usage);
	if ( status != 256)
		write(SK, "SUCCESS\n\0", 9);
	else
		write(SK, "ls : no such file or directory.\nERROR\n\0", 39);
	}
	else
		write(SK, "ls : no such file or directory.\nERROR\n\0", 39);
//	write(1, "SUCCESS\n\0", 9);
	return (0);

}

int handle_cd(char *cmd, t_env *e)
{
	char *cwd;
	char **arrcmd;
	char *gg;

	arrcmd = NULL;
	cwd = NULL;
	getcwd(cwd, MAXPATHLEN);
	arrcmd = ft_strsplit(ft_strtrim(cmd), ' ');
	gg = NULL;
    if (!arrcmd[1] || (!ft_strncmp(arrcmd[1], "/\0", 2)))
        gg = ".";
    if (gg || (arrcmd[1] && check_path(arrcmd[1], e->ref) != -1))
    {
        if (!gg)
			gg = arrcmd[1];
	if (arrcmd[1] == NULL)
	{
		error_cmd_cd(SK, cmd, "", NULL);
		return(0);
	}
	if (chdir(gg) < 0)//ft_strtrim(ft_str_sub_until(cmd,3))) < 0)
		error_cmd_cd(SK, "cd", "No such file or directory.\nERROR\n\0", ft_strtrim(ft_str_sub_until(cmd,3)));
	else
		write(SK, "SUCCESS\n\0", 9);
	}
	else 
		error_cmd_cd(SK, "cd", "No such file or directory.\nERROR\n\0", ft_strtrim(ft_str_sub_until(cmd,3)));
	//		ft_putendl("oops cd fail");

	//exit_error("Fail cd");
	(void)(e);

	return(0);
}

void get_fct(char *cmd,	 t_env *e)
{
	char **array_cmd;
	int i;


	array_cmd = NULL;
	ft_putendl(ft_strtrim(cmd));
	array_cmd = ft_strsplit(ft_strtrim(cmd), ' ');
	i = ft_arraylen(array_cmd) -1 ;
	//array_cmd[i][ft_strlen(array_cmd[i]) -1 ] = '\0';//trim_array(array_cmd);
	if (ft_strncmp("ls\0", array_cmd[0], 3) == 0)
		handle_ls(array_cmd, e);
	else if (ft_strncmp("pwd", array_cmd[0],ft_strlen(array_cmd[0])) == 0)
		get_pwd(cmd, e);
	else if(ft_strncmp("cd", cmd, 2) == 0)
		handle_cd(cmd, e);
	else if(ft_strncmp("get ", cmd, 4) == 0)
		handle_get(cmd, e);
	else if (ft_strncmp("put ", cmd, 4) == 0)
		{
			ft_putendl("go to handle put server ");
			handle_put(cmd, e);
		}
	else if(ft_strequ("quit",cmd) == 1)
		handle_quit(cmd, e);
	else
		{
			ft_putendl("cmd not found");
			write(SK, "command not found\nERROR\n\0",25);
		}
}

void get_pwd(char *buf, t_env *e)
{
	char path[1024];
	
	ft_bzero(path, 1024);
	(void)buf;
	getcwd(path, sizeof(path));
	ft_putnbr((int)sizeof(path));
	ft_putendl(path);
	path[ft_strlen(path)] = '\n';
	path[ft_strlen(path) + 1] = '\0';
	write(SK,path,ft_strlen(path));
	write(SK, "SUCCESS\n\0", 9);
	write(1,path,ft_strlen(path));
	ft_bzero(path,1024);
}
