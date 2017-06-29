#include <sys/types.h>
//#include "stream.h"
#include "../includes/ft_p_cli.h"
#include <unistd.h>
#include <libft.h>
#include <stdlib.h>

void			create_stream(int fd, t_stream *stream)
{
	stream->fd = fd;
	
	stream->size = 0;//read(fd, stream->buf, 4096);
	stream->cursor = 0;
}

static ssize_t	ft_len_to_endline(int fd, char c, t_stream *buf)
{
	char	*endline;

	if (buf->cursor >= (size_t)buf->size)
	{
		buf->size = read(fd, buf->buf, BUFSIZE);
		buf->cursor = 0;
	}
	if (buf->size <= 0)
		return (-1);
	endline = ft_memchr(buf->buf + buf->cursor, c, buf->size - buf->cursor);
	if (endline == NULL)
		return (-1);
	else
		return (endline - (buf->buf + buf->cursor));
}

static char		*ft_strnjoin(char *s1, const char *s2, size_t s2len)
{
	char	*new;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		new = ft_strnew(s2len);
		ft_memcpy(new, s2, s2len);
	}
	else if (s2 == NULL)
		return (s1);
	else
	{
		new = ft_strnew(ft_strlen(s1) + s2len);
		ft_strcpy(new, s1);
		ft_strncat(new, s2, s2len);
		free(s1);
	}
	return (new);
}

static char		*read_til_next_line(int fd, t_stream *buf, char c)
{
	char	*newstr;
	ssize_t	len;

	newstr = NULL;
	while ((len = ft_len_to_endline(fd, c, buf)) == -1 && buf->size > 0)
	{
		newstr = ft_strnjoin(newstr, buf->buf + buf->cursor,
				buf->size - buf->cursor);
		buf->cursor = buf->size;
	}
	if (buf->size == 0)
		return (newstr);
	else if (buf->size == -1)
		return (NULL);
	newstr = ft_strnjoin(newstr, buf->buf + buf->cursor, len);
	if (newstr == NULL)
		return (NULL);
	buf->cursor += len + 1;
	return (newstr);
}

int				read_until(t_stream *stream, char **str, char c)
{
	char buf[BUFSIZE];
	int r;

	r = 0;
	ft_bzero(buf,BUFSIZE);
	while ((r = read(stream->fd, stream->buf, BUFSIZE)) > 0)
	{
		ft_putendl(buf);
		ft_bzero(buf,BUFSIZE);
	}
	(void)str;
	(void)c;
	if (r == -1)
		((*str = read_til_next_line(stream->fd, stream, c)));
	return (0);
/*
	
	if ((*str = read_til_next_line(stream->fd, stream, c)) == NULL)
		return (0);
	else
	return (1);*/
}