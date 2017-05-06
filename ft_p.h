#ifndef FT_P_H
#define FT_P_H

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "libft/libft.h"
#include <errno.h>

typedef struct	s_env
{
struct protoent	*prot;
int		socketid;
int		bindsocket;
struct sockaddr_in	serv_sock;
struct sockaddr_in	cli_sock;
}		t_env;
#endif
