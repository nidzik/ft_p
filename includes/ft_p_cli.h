#ifndef FT_P_CLI_H
#define FT_P_CLI_H

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../libft/libft.h"
#include <errno.h>
#include <arpa/inet.h>

#define BUFSIZE 2048
#define SK e->socketid

typedef struct	s_env
{
  struct hostent *serv;
  int		socketid;
  int		port;
  struct sockaddr_in	serv_sock;
}		t_env;

typedef struct  s_stream
{
    int         fd;
    char        buf[BUFSIZE];
    ssize_t     size;
    size_t      cursor;
} t_stream;

void	exit_error(char *err);
int             get_next_line(const int fd, char **line);
int             read_until(t_stream *stream, char **str, char c);
void            create_stream(int fd, t_stream *stream);
void			handle_get(char *cmd, t_env *e);
void			handle_put(char *cmd, t_env *e);
void			handle_rest(char *cmd, t_env *e);
#endif
