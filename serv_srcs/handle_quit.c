//HEADER

#include "ft_p.h"

void handle_quit(char *cmd, t_env *e)
{
	free(e);
	free (cmd);
	exit(0);
}
