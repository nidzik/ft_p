#include "ft_p.h"

char **cmd_to_split(char *cmd)
{
  char **array_cmd;

  array_cmd = NULL;
  array_cmd = ft_strsplit(cmd, ' ');
  return (array_cmd);
}
