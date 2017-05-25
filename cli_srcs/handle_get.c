//HEADER

#include "ft_p_cli.h"

void handle_get(char *cmd, t_env *e)
{
	int file;
	int r;
	char buf[BUFSIZE];

	
	if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0 )
		ft_putendl("ERROR");
	return;
	ft_bzero(buf,BUFSIZE);
	while (( r  = read(e->socketid, buf,BUFSIZE)) != EOF){
		if (r < 0)
			exit_error("Erorr reading buf");
		r = '\0';
		write(file, buf, r);
		ft_bzero(buf,BUFSIZE);
		if (r != BUFSIZE)
			break;
	}
	close(file);
	ft_putendl("closing file oklm");
}
