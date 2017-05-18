#ifndef FT_P_CLI_H
#define FT_P_CLI_H

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../libft/libft.h"
#include <errno.h>
#include <arpa/inet.h>

#define BUFSIZE 2058

typedef struct	s_env
{
  struct hostent *serv;
  int		socketid;
  int		port;
  struct sockaddr_in	serv_sock;
}		t_env;

void	exit_error(char *err);
int             get_next_line(const int fd, char **line);
#endif
