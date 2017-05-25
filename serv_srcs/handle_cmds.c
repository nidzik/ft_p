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

char *ft_str_sub_until(char *str, int n)
{
	int i;
	int j;
	char *ret = malloc(sizeof(char) * ft_strlen(str));

	j = 0;
	if (n == 0 || str == NULL )
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (i >= n)
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[i] = '\0';
	if (ret == NULL || ft_strcmp(ret, "") == 0)
		return (NULL);
	return (ret);
}

int handle_get(char *cmd, t_env *e)
{
	/*	int file;
	int pid;
	struct rusage usage;
	int status;
	
	if ((pid = fork()) < 0)
		exit (0);
	else if (pid == 0)
		{
			if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_RDONLY)) > 0)
				dup2(SK, file);
		exit (0);
		}
	else
		wait4(pid, &status, 0, &usage);
	
	*/

		int r;
	char buf[BUFSIZE];
	int i;
	int file;
	(void)e;
	ft_bzero(buf,BUFSIZE);
	r = 0;
	i = 0;
	if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_RDONLY)) > 0){
		while (( r  = read(file, buf,BUFSIZE)) != EOF)
			{
			if (r < 0)
				exit_error("Erorr reading buf");
			//			ft_putstr_fd(buf,SK);
			write(SK, buf, r);
			ft_bzero(buf,BUFSIZE);
			if (r != BUFSIZE)
				break;
			r = 0;
		}
	}
	

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
	else if (ft_strncmp("pwd", cmd, 3) == 0)
		get_pwd(cmd, e);
	else if(ft_strncmp("cd", cmd, 2) == 0)
		handle_cd(cmd, e);
	else if(ft_strncmp("get", cmd, 3) == 0)
		handle_get(cmd, e);
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
