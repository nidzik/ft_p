//HEADER

#include "ft_p_cli.h"

void handle_rest(char *cmd, t_env *e)
{
	int r;
    char buf[BUFSIZE];
	
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	ft_bzero(buf,BUFSIZE);
	r = 0;
	ft_putendl("receive");
	while (( r  = read(e->socketid, buf,BUFSIZE)) != EOF){
		if (r < 0)
			exit_error("Erorr reading buf");
		ft_putstr(buf);
		ft_bzero(buf,BUFSIZE);
		if (r != BUFSIZE)
			break;
	}
}
