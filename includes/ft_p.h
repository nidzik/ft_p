#ifndef FT_P_H
#define FT_P_H

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../libft/libft.h"
#include <errno.h>

#define PORT 4242
#define LSS 27763
#define CDD 25444
#define GETT 26469
#define PUTT 28789
#define PWDD 28791
#define QUITT 29045
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
void get_fct(char *cmd, t_env *e);
void    handle(int clifd);
void get_pwd(char *buf, t_env *e);
char **cmd_to_split(char *cmd);
void    error_cmd_cd(int sk, char *cmd, char *error, char *args);
#endif
