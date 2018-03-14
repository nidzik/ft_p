#include "ft_p_cli.h"

void exit_error(char *err)
{
  ft_putendl(err);
  exit(1);
}

void error_cmd_cd(int sk, char *cmd, char *erorr, char *args)
{
	if (args == NULL || ft_strcmp(args, "") == 0)
		write(sk, "Usage : cd <PATH>\nERROR\n\0", 25);
	else
		write(sk, "cd : No such file or directory\nERROR\n\0", 38);
//	ft_putstr_fd(cmd, sk);
//	ft_putstr_fd(" : ", sk);
//	ft_putendl_fd(erorr, sk);
//	ft_putchar_fd('\0', sk);

	(void)cmd;
	(void)erorr;
}
