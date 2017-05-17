#include "ft_p_cli.h"

static void init_env(t_env *e, char **av)
{
  e->port = ft_atoi(av[2]);
  e->socketid = 0;
  e->serv = gethostbyname(av[1]);
  if (e->serv == NULL)
    {
      ft_putendl("No such ho");
      exit(0);
    }
  ft_bzero(&e->serv_sock, sizeof(e->serv_sock));
  e->serv_sock.sin_family = PF_INET;
  // IF is not 127.0.0.1 but "localhost" do memcpy else do inet
  //  ft_memcpy(&e->serv_sock.sin_addr.s_addr, e->serv->h_addr, e->serv->h_length);
  e->serv_sock.sin_addr.s_addr = inet_addr(av[1]);
  //e->serv_sock.sin_addr.s_addr = htons(e->serv->h_addr);
  e->serv_sock.sin_port = htons(e->port);
}

static void connect_to_socket(t_env * e)
{
 if ((e->socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    exit_error("Error while opening the socket.. Exiting");
  if (connect(e->socketid,(struct sockaddr *)&e->serv_sock,sizeof(e->serv_sock)) < 0)
    exit_error("Error while connecting the socket, if your using localhost try 127.0.0.1");
  ft_putendl("Welcome");
}

static void send_cmd_and_receive(t_env *e)
{
  int r;
  char buf[BUFSIZE];
  
  ft_bzero(buf,BUFSIZE);
  r = 0;
  while(1){
                  write(1,"ftp>",4);
  if ((r = read(0, buf, BUFSIZE)) > 0)
    {

      buf[r] = '\0';
      if (write(e->socketid, buf, ft_strlen(buf)) < 0)
	exit_error("Error, can't write on the socket.");
      ft_bzero(buf,256);
      r = 0;
	  ft_putendl("receive");
	  if (( r = read(e->socketid, buf,BUFSIZE)) < 0)
		  exit_error("Error, can't write on the socket.");
	  ft_putnbr(r);
      buf[r] = '\0';
      if (r < 0)
		  exit_error("Erorr reading buf");
	  ft_putendl(buf);
	  ft_bzero(buf,256);
	  r = 0;
    }
  }
}

int main(int ac, char **av)
{
  t_env *e;

  if (ac < 3)
    exit_error("usage ./client hostname port\n");
  e = (t_env *)malloc(sizeof(t_env));
  init_env(e, av);
  connect_to_socket(e);
  send_cmd_and_receive(e);
  ft_putendl("Closing");  
  return(0);
}
