#include "ft_p.h"
#include <sys/param.h>

int			handle_ls(char **cmd, t_env *e)
{
	int					pid;
	int					status;
	struct rusage   usage;
	int					i;
	int stdio[3];

	stdio[1] = SK;
	stdio[2] = SK;
	ft_print_array(cmd);
	ft_putendl("starting fork");
	if ((pid = fork()) < 0)
		exit (0);
	else if (pid == 0)
		{
			i = -1;
			while (++i < 3)
				if (stdio[i] != -1 && stdio[i] != i)
					dup2(stdio[i], i);
			execv("/bin/ls", (cmd));
			exit(1);
		}
	else
		wait4(pid, &status, 0, &usage);
	return (0);

}

int handle_cd(char *cmd, t_env *e)
{
	char *cwd;

	cwd = NULL;
	getcwd(cwd, MAXPATHLEN);
	if (chdir(ft_strtrim(ft_str_sub_until(cmd,3))) < 0)
		error_cmd_cd(SK, "cd", "No such file or directory.", ft_strtrim(ft_str_sub_until(cmd,3)));
	else
		write(SK, "SUCCESS\n\0", 9);

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
	if (ft_strncmp("ls", cmd, 2) == 0)
		handle_ls(array_cmd, e);
	else if (ft_strcmp("pwd", cmd) == 0)
		get_pwd(cmd, e);
	else if(ft_strncmp("cd", cmd, 2) == 0)
		handle_cd(cmd, e);
	else if(ft_strncmp("get ", cmd, 4) == 0)
		handle_get(cmd, e);
	else if (ft_strncmp("put ", cmd, 4) == 0)
		{
			ft_putendl("go to handle put server ");
			handle_put(ft_strtrim(cmd), e);
		}
	else if(ft_strcmp("quit",cmd))
		handle_quit(cmd, e);
	else
		{
			ft_putendl("cmd not found");
			write(SK, "error cmd\n",10);
		}
}

void get_pwd(char *buf, t_env *e)
{
	char path[1024];
	
	(void)buf;
	getcwd(path, sizeof(path));
	ft_putnbr((int)sizeof(path));
	path[ft_strlen(path)] = '\n';
	path[ft_strlen(path) + 1] = '\0';
	write(SK,path,ft_strlen(path));
	write(0,path,sizeof(path));
	bzero(path,1024);
}
