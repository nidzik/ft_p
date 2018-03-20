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
	char		*ref_path;
  struct sockaddr_in	serv_sock;
}		t_env;

typedef struct  s_stream
{
    int         fd;
    char        buf[BUFSIZE];
    ssize_t     size;
    size_t      cursor;
} t_stream;

typedef struct	s_file
{
	int			file;
	int			r;
	int 		cmp;
	char		*namefile;
	char		buf[BUFSIZE];
	char		**arr;
}				t_file;

void			exit_error(char *err);
int             get_next_line(const int fd, char **line);
int             read_until(t_stream *stream, char **str, char c);
void            create_stream(int fd, t_stream *stream);
int				handle_get(char *cmd, t_env *e);
int				handle_put(char *cmd, t_env *e);
int				handle_rest(char *cmd, t_env *e);
void			handle_quit(char *cmd, t_env *e);
int				login(t_env *e);
int				check_cmd(char *cmd, t_env *e);
int				snd_rcve_cmd(int *cmp, char *buf, t_env *e, int r);
void			handle_error_snd_rcve(int r);
void			init_snd_rcve(int *cmp, int *r);
int				return_error(char *str);
#endif
