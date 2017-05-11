#ifndef FT_P_H
#define FT_P_H

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../libft/libft.h"
#include <errno.h>

#define PORT 4242
#define LS 27763
#define CD 25444
#define GET 26469
#define PUT 28789
#define PWD 28791
#define QUIT 29045
#define IDK 2673
#define SK e->accept_socket

typedef struct	s_env
{
struct protoent	*prot;
  int		port;
  int		pid;
  int		socketid;
  int		sonid;
  int		accept_socket;
  int		cli_size;
  struct sockaddr_in	serv_sock;
  struct sockaddr_in	cli_sock;
  char 	      	**args;
}		t_env;

void exit_error(char *err);
void get_fct(int req, t_env *e);

#endif
