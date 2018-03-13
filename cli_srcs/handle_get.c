
//HEADER

#include "ft_p_cli.h"

void handle_get(char *cmd, t_env *e)
{
	int file;
	int r;
	char buf[BUFSIZE];
	char *namefile;
	char **arr;

	arr = NULL;
	arr = ft_strsplit(ft_strtrim(cmd), ' ');
	if (ft_arraylen(arr) == 2)
		namefile = arr[1];
	else
		namefile = ft_str_last_slash(arr[1]);
	ft_putendl(arr[1]);
	if ((file = open(namefile, O_WRONLY)) < 0 )
	{
		ft_putendl("ERROR can't open the file");
		return;
	}
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	ft_bzero(buf,BUFSIZE);
	ft_putchar('.');
	while (( r  = read(e->socketid, buf,BUFSIZE)) > 0){
		if (r < 0)
			exit_error("Erorr reading buf");
		write(file, buf, r);
		ft_bzero(buf,BUFSIZE);
		if (r != BUFSIZE)
			break;
		r = 0;
	}
	close(file);
	ft_putendl("closing file oklm");
}


void handle_put(char *cmd, t_env *e)
{
   int r;
    char buf[BUFSIZE];
	char rep[3];
    int file;

    ft_putendl(ft_strtrim(ft_str_sub_until(cmd, 4)));
    ft_bzero(buf,BUFSIZE);
    r = 0;
    if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_RDONLY)) > 0)
		{
			if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
				ft_putendl("error write");
			if (read(SK,rep,3 ) < 0)
				ft_putendl("read rep error");
			//        exit_error("Error, can't write on the socket.");
			while (( r  = read(file, buf,BUFSIZE)) != EOF)
				{
					if (r < 0)
						exit_error("Erorr reading buf");
					write(SK, buf, r);
					//write(1, buf, r);
					ft_bzero(buf,BUFSIZE);
					if (r != BUFSIZE)
						break;
					r = 0;
				}
		}
			else
				ft_putendl("error open file");
	close(file);	
	return;
}
