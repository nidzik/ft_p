//HEADER

#include "ft_p.h"

void handle_quit(char *cmd, t_env *e)
{
	free(e);
	(void)cmd;
	exit(0);
}
