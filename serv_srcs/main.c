#include "ft_p.h"

void init_env(t_env *e)
{
  e->prot = getprotoent();
  e->socketid = 0;
  e->accept_socket = 0;
  e->pid = 0;
  e->cli_size = 0;
  ft_bzero(&e->serv_sock, sizeof(e->serv_sock));
  e->serv_sock.sin_family  = PF_INET;
  e->serv_sock.sin_port = htons(PORT);
  e->serv_sock.sin_addr.s_addr = htons(INADDR_ANY);
  
}
int main(int ac, char **av)
{
  t_env *e;

  e = (t_env *)malloc(sizeof(t_env));
  init_env(e);
  (void)ac;
  (void)av;
  ft_putendl(e->prot->p_name);
  ft_putnbr(e->prot->p_proto);

  if ((e->socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      ft_putnbr(errno);
      ft_putendl("socket error server side.\nExiting...");
      exit(0);
    }

  if ((bind(e->socketid, (struct sockaddr *) &e->serv_sock, sizeof(e->serv_sock))) < 0)
    {
      char *bouh = strerror(errno);
      ft_putendl(bouh);
      ft_putendl("Error while binding the socket.\nExiting...");
      exit(0);
    }

  if (listen(e->socketid, 5) < 0 )
    {
      ft_putendl("Error while listing. Exiting...");
      exit(1);
    }

  while(42)
    {
      if ((e->accept_socket = accept(e->socketid, (struct sockaddr *) &e->cli_sock, (unsigned int *)&e->cli_size)) < 0)
	{
	        ft_putendl("Error while accepting the socket. Exiting...");
		exit(1);
	}
      if ((e->pid = fork()) == 0)
	{
	  close(e->socketid);
	  ft_ftp(e->accept_socket);
	  close(e->accept_socket);
	  exit(0);
	}
    }
  return(0);
}

void ft_ftp(int accepted_sk)
{
  (void) accepted_sk;
  ft_putendl("ur in !");
}
