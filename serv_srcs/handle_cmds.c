#include "ft_p.h"
# define BUFSIZE 4096
# define MAXPATHLEN 256

# define ACK  'O'
# define ERR  'K'
# define CD   'C'
# define LS   'L'
# define GET  'G'
# define PUT  'P'
# define PWD  'W'
# define QUIT 'Q'
# define FT_MIN(x, y) (x) < (y) ? (x) : (y)
typedef struct	s_state
{
	int			id;
	int			running;
	char		rootdir[MAXPATHLEN];
} t_state;

typedef struct	s_stream
{
	int			fd;
	char		buf[BUFSIZE];
	ssize_t		size;
	size_t		cursor;
} t_stream;
  
typedef int		(*t_handler)(t_stream *, t_state *);

void			fill_buf(t_stream *stream)
{
	if (stream->size > 0 && (ssize_t)stream->cursor >= stream->size)
	{
		stream->size = read(stream->fd, stream->buf, 4096);
		stream->cursor = 0;
	}
}

int				read_u8(t_stream *stream, uint8_t *c)
{
	fill_buf(stream);
	if (stream->size <= 0)
		return (0);
	else
	{
		*c = stream->buf[stream->cursor++];
		return (1);
	}
}

int				read_u32be(t_stream *stream, uint32_t *nbr)
{
	uint8_t	*ptr;
	int		res;

	ptr = (uint8_t*)nbr;
	res = read_u8(stream, ptr + 0)
			&& read_u8(stream, ptr + 1)
			&& read_u8(stream, ptr + 2)
			&& read_u8(stream, ptr + 3);
	if (res)
		*nbr = ntohl(*nbr);
	return (res);
}



int				read_s8(t_stream *stream, int8_t *c)
{
	fill_buf(stream);
	if (stream->size <= 0)
		return (0);
	else
	{
		*c = stream->buf[stream->cursor++];
		return (1);
	}
}
int				read_s32be(t_stream *stream, int32_t *nbr)
{
	int8_t	*ptr;
	int		res;

	ptr = (int8_t*)nbr;
	res = read_s8(stream, ptr + 0)
			&& read_s8(stream, ptr + 1)
			&& read_s8(stream, ptr + 2)
			&& read_s8(stream, ptr + 3);
	if (res)
		*nbr = (int32_t)ntohl(*nbr);
	return (res);
}


static int	run_cmd(char *cmd, char **args, int stdio[3])
{
	int				pid;
	int				status;
	struct rusage	usage;
	int				i;
	(void)args;
	if ((pid = fork()) < 0)
		return (0);
	else if (pid == 0)
	{
		i = -1;
		while (++i < 3)
			if (stdio[i] != -1 && stdio[i] != i)
				dup2(stdio[i], i);
		execl(cmd, "/", NULL);
		ft_putendl("EXECV FAIL");
		exit(1);
	}
	else
		wait4(pid, &status, 0, &usage);
	return (1);
}
int				read_string(t_stream *stream, char **str, size_t *size)
{
	uint32_t	strsize;
	uint32_t	striter;
	int			oldstriter;
	char		*tmp;

	if (!read_u32be(stream, &strsize))
		return (0);
	*str = malloc(sizeof(char) * (strsize + 1));
	(*str)[strsize] = '\0';
	tmp = *str;
	striter = 0;
	oldstriter = 0;
	while (striter < strsize && stream->size > 0)
	{
		striter += FT_MIN(stream->size - stream->cursor, strsize - striter);
		ft_memmove(tmp, stream->buf + stream->cursor, striter - oldstriter);
		tmp += striter - oldstriter;
		stream->cursor += striter - oldstriter;
		oldstriter = striter;
		if (striter < strsize)
			fill_buf(stream);
	}
	if (size != NULL)
		*size = (size_t)strsize;
	return (striter == strsize);
}
int			handle_ls(t_stream *stream, t_state *state)
{
	char			*line;
	char			**args;
	int				stdio[3];
	int				i;

	(void)state;
	if (!read_string(stream, &line, NULL))
		return (0);
	stdio[0] = -1;
	stdio[1] = stream->fd;
	stdio[2] = stream->fd;
	args = NULL;//ft_strsplitwith(line, " \t", NULL);
	i = 1;
	/*while (args[i] != NULL)
	{
		if (ft_strstr(args[i], "..") || args[i][0] == '/')
			args[i] = "";
		i++;
		}*/
	run_cmd("/bin/ls", args, stdio);
	write(stdio[1], "\0", 1);
	return (1);
}
/*static void ft_ls(t_env *e) 
{
  char buf[256];
  int i;
  //  pid_t cpid;
  i = 0;
  ft_bzero(buf,256);
  int				stdio[3];
 stdio[0] = -1;
	stdio[1] = SK;
	stdio[2] = SK;
	run_cmd("/bin/ls","gg",stdio);*/
  
  /*  while ( (i = read(0, buf, ft_strlen(buf))) > 0)
    {
      if (execl("/bin/ls",".", NULL) < 0)
	ft_putendl("error during ls");
      else
	{
	  buf[i] = '\0';
	  (void)e;
	  write(SK, buf, ft_strlen(buf));
	  ft_putstr("::");
	  ft_putendl(buf);
	  break;
	}
	}*/
//}*/
int		handle_fail(t_stream *stream, t_state *state)
{
  //	send_failure(stream, NULL);
  (void)stream;
	state->running = 0;
	return (0);
}
int handle_cd(t_stream *stream, t_state *state)
{
  (void)stream;
  (void)state;
  return (1);
}
void			create_stream(int fd, t_stream *stream)
{
	stream->fd = fd;
	stream->size = read(fd, stream->buf, 4096);
	stream->cursor = 0;
}
void	handle_cmd(int cmd, t_stream *stream, t_state *state)
{
	static t_handler	handlers[27];
	int					i;

	if (handlers[26] == NULL)
	{
		i = 0;
		while (i < 27)
			handlers[i++] = handle_fail;
		handlers[CD - 'A'] = handle_cd;
		handlers[LS - 'A'] = handle_ls;
		//handlers[GET - 'A'] = handle_get;
		//handlers[PUT - 'A'] = handle_put;
		//handlers[PWD - 'A'] = handle_pwd;
		//handlers[QUIT - 'A'] = handle_quit;
	}
	handlers[cmd - 'A'](stream, state);
}
void	handle(int clifd)
{
	t_stream	stream;
	int8_t		cmd;
	t_state		state;

	getcwd(state.rootdir, MAXPATHLEN);
	state.running = 1;
	state.id = clifd;
	create_stream(clifd, &stream);
	while (state.running && read_s8(&stream, &cmd))
	{
		if (!ft_isalpha(cmd))
			handle_fail(&stream, &state);
		else
		{
			ft_putstr("Handling cmd : ");
			ft_putchar(ft_toupper(cmd));
			ft_putstr(" ");
			ft_putendl("");
			handle_cmd(cmd, &stream, &state);
		}
	}
}
void get_fct(int req,  t_env *e)
{
  (void)req;
  //  write(SK,"ftp>",4);
    if (req == 0){
  int                             pid;
        int                             status;
        struct rusage   usage;
        int                             i;
        int stdio[3];
	stdio[1] = SK;
	stdio[2] = SK;
	ft_putendl("starting fork");
        if ((pid = fork()) < 0)
                exit (0);
        else if (pid == 0)
        {
                i = -1;
                while (++i < 3)
                        if (stdio[i] != -1 && stdio[i] != i)
                                dup2(stdio[i], i);
                  execl("/bin/ls", "/", NULL  );
                //                execl(cmd, "/", NULL);
                  //                ft_putendl("EXECV FAIL");
		  //                printf("coucou");
		  //		  write(SK,"\0",1);
		  	ft_putendl("end fork");
                exit(1);
        }
        else
                wait4(pid, &status, 0, &usage);
		ft_putendl("writing \\0");
		//	write(stdio[1], "\0", 1);
  }
  else
    write(SK,"command not found\n\0",18 );
  //  if (req == LS)
  //handle(e->accept_socket);
}


void get_pwd(char *buf, t_env *e)
{
  char path[1024];

  (void)buf;
  getcwd(path, sizeof(path));
  ft_putnbr((int)sizeof(path));
  path[ft_strlen(path)] = '\0';
  write(SK,path,ft_strlen(path));
  write(0,path,sizeof(path));
  bzero(path,1024);
  //write (SK,"coucou\n\0",8);
  //write (0,"\0",1);
}
