//HEADER

#include "ft_p_cli.h"

void handle_get(char *cmd, t_env *e)
{
	int file;
	int r;
	char buf[BUFSIZE];
	char *namefile;

	namefile = ft_strtrim(ft_str_sub_until(cmd, 4));
//	ft_putendl(namefile);
	if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0 )
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
    int file;

    ft_putendl("ft_get");
    ft_bzero(buf,BUFSIZE);
    r = 0;
    if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_RDONLY)) > 0){
        while (( r  = read(file, buf,BUFSIZE)) != EOF)
            {
            if (r < 0)
                exit_error("Erorr reading buf");
            write(SK, buf, r);
            ft_bzero(buf,BUFSIZE);
            if (r != BUFSIZE)
                break;
            r = 0;
        }
    }
return;
}
