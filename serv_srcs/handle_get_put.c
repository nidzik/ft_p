/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:02:21 by nidzik            #+#    #+#             */
/*   Updated: 2018/04/02 16:47:53 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void		init_file(t_file *f)
{
	f->r = 0;
	f->file = 0;
	f->arr = NULL;
	f->namefile = 0;
	ft_bzero(f->buf, BUFSIZE);
}

static int		check_get(t_file *f, char *cmd, t_env *e)
{
	f->arr = create_tab(cmd);
	f->namefile = ft_strdellastslash(f->arr[1]);
	if (f->namefile != NULL)
	{
		if ((check_path(f->namefile, e->ref) == -1))
		{
			write(SK, "get : no such file or directory.\nERROR\n\0", 39);
			return (-1);
		}
		else if (check_ifdirexist(f->arr[1]) == -1)
		{
			write(SK, "get : no such file or directory\nERROR\n\0", 39);
			return (-1);
		}
	}
	return (0);
}

int				handle_get(char *cmd, t_env *e)
{
	t_file	f;

	init_file(&f);
	if (check_get(&f, cmd, e) == -1)
		return (-1);
	if ((f.file = open(f.arr[1], O_RDONLY)) >= 0)
	{
		while ((f.r = read(f.file, f.buf, BUFSIZE)) != EOF)
			if (core_get(SK, &f) == -42)
				break ;
		close(f.file);
	}
	else
		write(SK, "get : no such file or directory\nERROR\n\0", 39);
	if (f.r == 0 && f.file != -1)
		write(SK, "EMPTY\n\0", 7);
	ft_strdel(&(f.namefile));
	ft_arraydel(f.arr);
	return (0);
}

static int		check_put(t_file *f, char *cmd, t_env *e)
{
	char *tmp;

	f->namefile = get_cmd(cmd);
	tmp = ft_str_last_slash(f->namefile);
	if (!f->namefile || check_ifdirexist(tmp) >= 0)
	{
		write(SK, "put : file already exist.\nERROR\n\0", 33);
		return (-1);
	}
	if ((f->file = open(tmp, O_WRONLY | O_CREAT, S_IRUSR | \
					S_IWUSR)) < 0)
	{
		ft_strdel(&tmp);
		return (return_error_s(\
					"put : can't open the file.\nERROR\n\0", -1, SK));
	}
	write(SK, "yep\0", 4);
	return (0);
}

int				handle_put(char *cmd, t_env *e)
{
	t_file	f;

	init_file(&f);
	if (check_put(&f, cmd, e) == -1)
		return (-1);
	while ((f.r = read(SK, f.buf, BUFSIZE)) != EOF)
	{
		ft_putendl(f.buf);
		if (ft_strsearch(f.buf, "EMPTY\n\0"))
		{
			write(SK, "Upload completed.\nSUCCESS\n\0", 27);
			break ;
		}
		write(f.file, f.buf, f.r);
		if (core_put(SK, &f) == -42)
			break ;
		ft_bzero(f.buf, BUFSIZE);
	}
	close(f.file);
	ft_arraydel(f.arr);
	ft_strdel(&f.namefile);
	return (0);
}
