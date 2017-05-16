#include "ft_p.h"

static void init_env(t_env *e, char **av)
{
  e->port = ft_atoi(av[1]);
  e->prot = getprotobyname("tcp");
  e->socketid = 0;
  e->accept_socket = 0;
  e->pid = 0;
  e->cli_size = 0;
  ft_bzero(&e->serv_sock, sizeof(e->serv_sock));
  e->serv_sock.sin_family  = AF_INET;
  e->serv_sock.sin_port = htons(e->port);
  e->serv_sock.sin_addr.s_addr = htonl(INADDR_ANY);
  
}

static void sock_bind_listen(t_env *e)
{
      if ((e->socketid = socket(PF_INET, SOCK_STREAM, e->prot->p_proto)) < 0)
    exit_error("socket error server side.\nExiting...");
      if ((bind(e->socketid, (struct sockaddr *) &e->serv_sock, sizeof(e->serv_sock))) < 0)
    exit_error("Error while binding the socket.\nExiting...");
      if (listen(e->socketid, 5) < 0 )
	exit_error("Error while listing. Exiting...");  
}

static void ft_ftp(t_env *e)
{
  int req;
  int r;
  char buf[128];
  
  req = 0;
  ft_putendl("Reading the cmd from socket...");
  while(42)
	  if ((r = read(SK, (char *)buf, sizeof(buf))) >0)
    {
      if (r <= 0)
	exit_error("Error while readding ");
            buf[r] = '\0';
	    //      write(SK, &buf,sizeof(buf));

      //req = ntohs(req);
      //      ft_putnbr(req);
      //ft_putchar('\n');
      /*      if (req == LSS || req == CDD || req == GETT || req == PUTT || req == PWDD || req == QUITT){	
	if (write(SK, "ur cmd was received\n", 21) < 0)
	  ft_putendl("failure writing on the socket");
	get_fct(req,e);
	}
	else*/
      //if (write(SK, "cmd unknow\n", 11) < 0)
      //  ft_putendl("failure writing on the socket");
      //get_cmd(req);
	    ft_putendl(buf);
	          if (ft_strncmp("ls", buf, 2) == 0)
            	get_fct(0,e);
		  else if (ft_strncmp("pwd", buf, 3) == 0)
		    get_pwd(buf, e);
		  else
		    ft_putendl("error cmd");
		  ft_putendl("bz buf");
            ft_bzero(buf, 128);
	req = 0;
	r = 0;
    }
}

static void boucle_accept(t_env *e)
{
  while(42)
    {
      if ((e->accept_socket = accept(e->socketid, (struct sockaddr *) &e->cli_sock, (unsigned int *)&e->cli_size)) < 0)
	exit_error("Error while accepting the socket. Exiting...");
      if ((e->pid = fork()) == 0)
	{
	  close(e->socketid);
	  //handle
	  ft_ftp(e);
	  close(e->accept_socket);
	  exit(0);
	}
    }
}

int main(int ac, char **av)
{
  t_env *e;
  
  if (!(e = (t_env *)malloc(sizeof(t_env))))
      exit_error("Error : malloc fail");
      if (ac < 2)
	exit_error("usage ./server port");
      init_env(e, av);
      sock_bind_listen(e);
      boucle_accept(e);
  return(0);
}

