#include "ft_p.h"
#include <sys/param.h>
char **drop(char **cmd)
{
//	if (ft_arraylen(cmd) == 1)
//		return (NULL);
	if (cmd != NULL)
		(void)*cmd++;
	return cmd;	
}

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
	char *one;
	char *tow;
	
	cwd = NULL;
	ft_putendl(one = getcwd(cwd, MAXPATHLEN));
	ft_putendl(cmd);
	tow = ft_strcat(one, ft_strsub(cmd, 0, 3));
	ft_putendl(tow);
	if (chdir(cmd) < 0)
		exit_error("Fail cd");
	(void)(e);
	write(SK, "\0", 1);
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
	else if (ft_strncmp("pwd", cmd, 3) == 0)
		get_pwd(cmd, e);
	else if(ft_strncmp("cd", cmd, 2) == 0)
		handle_cd(cmd, e);
	else
		write(SK, "error cmd\n",10);
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
