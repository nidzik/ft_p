/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 17:16:41 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/23 19:20:42 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# ifdef __APPLE__
#  include <netdb.h>
#  include <sys/socket.h>
#  include <arpa/inet.h>
#  include <errno.h>
#  include "../libft/libft.h"
#  include <dirent.h>
#  include <sys/param.h>
#  include <sys/stat.h>
# elif __linux__
#  include <crypt.h>
#  include <sys/stat.h>
#  include <sys/param.h>
#  include <sys/socket.h>
#  include "../libft/libft.h"
#  include <sys/types.h>
#  include <sys/time.h>
#  include <sys/resource.h>
#  include <sys/wait.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <netinet/ip.h>
#  include <netdb.h>
# else
#  error "unknown plateform"
# endif
# define PORT 4242
# define LSS 27763
# define CDD 25444
# define GETT 26469
# define PUTT 28789
# define PWDD 28791
# define QUITT 29045
# define IDK 2673
# define SK e->accept_socket
# define BUFSIZE 2048

typedef struct			s_env
{
	struct protoent		*prot;
	int					port;
	int					pid;
	int					socketid;
	char				*ref;
	int					sonid;
	int					accept_socket;
	int					cli_size;
	struct sockaddr_in	serv_sock;
	struct sockaddr_in	cli_sock;
	char				**args;
}						t_env;

typedef	struct			s_file
{
	int				r;
	int				file;
	char			**arr;
	char			*namefile;
	char			buf[BUFSIZE];
}						t_file;

void					exit_error(char *err);
void					get_fct(char *cmd, t_env *e);
void					handle(int clifd);
void					get_pwd(char *buf, t_env *e);
char					**cmd_to_split(char *cmd);
int						error_cmd_cd(int sk, char *cmd, char *error,\
									char *args);
int						handle_get(char *cmd, t_env *e);
int						handle_put(char *cmd, t_env *e);
void					handle_quit(char *cmd, t_env *e);
int						check_path(char *path, char *ref_path);
int						connect_me(int sockid, t_env *e);
int						create_pass(char *pass, int sockid);
int						verify_pass(char *pass, int sockid);
int						check_ifdirexist(char *path);
void					core_ls(int i, char *arg, int *status);
void					check_return_ls(int status, int sock);
void					check_ret_cd(int sk, char *name, char **arr);
char					*get_cmd(char *cmd);
char					**create_tab(char *str);
int						create_ref(t_env *e);
int						core_connect_pass(t_env *e, int sockid);
int						check_pass(char *pass, int sockid);
int						return_error_s(char *err, int i, int sk);
int						core_put(int sk, t_file *f);
int						core_get(int sk, t_file *f);
#endif
