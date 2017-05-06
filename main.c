#include "ft_p.h"

void init_env(t_env *e)
{
  e->prot = getprotoent();
  e->socketid = 0;
  e->bindsocket = 0;
  ft_bzero(&e->serv_sock, sizeof(e->serv_sock));
  e->serv_sock.sin_family  = PF_INET;
  e->serv_sock.sin_port = htons(4242);
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

  if ((e->bindsocket = bind(e->socketid, (struct sockaddr *) &e->serv_sock, sizeof(e->serv_sock))) < 0)
    {
      char *bouh = strerror(errno);
      ft_putendl(bouh);
      ft_putendl("Error while binding the socket.\nExiting...");
      exit(0);
    }
  
  return(0);
}
