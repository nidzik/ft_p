#ifndef FT_P_H
#define FT_P_H

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../libft/libft.h"
#include <errno.h>

#define PORT 4242

typedef struct	s_env
{
struct protoent	*prot;
  int		pid;
  int		socketid;
  int		sonid;
  int		accept_socket;
  int		cli_size;
  struct sockaddr_in	serv_sock;
  struct sockaddr_in	cli_sock;
}		t_env;

void ft_ftp(int accepted_sk);



#endif
