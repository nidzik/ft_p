#include "ft_p.h"

char **cmd_to_split(char *cmd)
{
  char **array_cmd;

  array_cmd = NULL;
  array_cmd = ft_strsplit(cmd, ' ');
  return (array_cmd);
}

int check_path(char *path, char* path_ref)
{
	if (!ft_strncmp(path, path_ref, ft_strlen(path_ref) - 1))
	{
		ft_putendl("YES..");
		return (1);
	}
	else
	{
		ft_putendl("NO..");
		return (-1);
	}
}
