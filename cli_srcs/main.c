#include "ft_p_cli.h"
void init_env(t_env *e, char **av)
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
  ft_memcpy(&e->serv_sock.sin_addr.s_addr, e->serv->h_addr, e->serv->h_length);
  //e->serv_sock.sin_addr.s_addr = htons(e->serv->h_addr);
  e->serv_sock.sin_port = htons(e->port);
}

char *ft_fgets(char *out, int size, FILE *in) 
{ 
   int ch; 
   char *buf = out; 
   while (--size > 0 && (ch = fgetc(in)) != EOF) { 
      if ((*buf++ = ch) == '\n')  /* EOL */ 
         break; 
   } 
   *buf = '\0'; 
   return (ch == EOF && buf == out) ? NULL : out; 
}
int main(int ac, char **av)
{
  t_env *e;
  char buf[BUFSIZE];
  
  if (ac < 3)
    {
      ft_putendl("usage ./client hostname port\n");
       exit(0);
    }
  e = (t_env *)malloc(sizeof(t_env));
  init_env(e, av);
  if ((e->socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      ft_putendl("Error while opening the socket.. Exiting");
      exit(0);
    }
  if (connect(e->socketid,(struct sockaddr *)&e->serv_sock,sizeof(e->serv_sock)) < 0)
    {
      ft_putendl("Error while connecting the socket");
      exit(0);
    }
      ft_putendl("Welcome");

      int i = 0;
      ft_bzero(buf,256);
      /*char **coucou = NULL;
      i = get_next_line(0, coucou);
      ft_putendl(*coucou);-*/
          if ((read(0, buf, BUFSIZE)) > 0)
	{
	  while (buf[i])
	   ft_putchar(buf[i++]);
	
	  i = 0;
      ft_bzero(buf,256);
	}
	  write(e->socketid,buf,strlen(buf));
  ft_putendl("Closing");  
  return(0);
}
