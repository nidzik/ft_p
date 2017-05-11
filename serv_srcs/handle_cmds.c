#include "ft_p.h"


static void ft_ls(t_env *e) 
{
  char buf[256];
  int i;

  i = 0;
  ft_bzero(buf,256);
  while ( (i = read(0, buf, ft_strlen(buf))) > 0)
    {
      if (execl("/bin/ls",".", NULL) < 0)
	ft_putendl("error during ls");
      else
	{
	  buf[i] = '\0';
	  (void)e;
	  write(SK, buf, ft_strlen(buf));
	  ft_putstr("::");
	  ft_putendl(buf);
	  break;
	}
    }
}
void get_fct(int req,  t_env *e)
{
  if (req == LS)
    ft_ls(e);
}

