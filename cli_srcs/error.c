#include "ft_p_cli.h"

void exit_error(char *err)
{
  ft_putendl(err);
  exit(1);
}

int return_error(char *str)
{
	ft_putstr(str);
	return (-1);
}
