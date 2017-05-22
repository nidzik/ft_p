#include "ft_p_cli.h"

void exit_error(char *err)
{
  ft_putendl(err);
  exit(1);
}

void error_cmd_cd(int sk, char *cmd, char *erorr, char *args)
{
	if (args == NULL || ft_strcmp(args, "") == 0)
		write(sk, "Usage : cd <PATH>\n\0", 19);
	else
		write(sk, "ERROR : cd : NoSUCH file dor fcking directory\n\0", 47);
//	ft_putstr_fd(cmd, sk);
//	ft_putstr_fd(" : ", sk);
//	ft_putendl_fd(erorr, sk);
//	ft_putchar_fd('\0', sk);

	(void)cmd;
	(void)erorr;
}
