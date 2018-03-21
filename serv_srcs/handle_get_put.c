/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:02:21 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/21 19:42:32 by nidzik           ###   ########.fr       */
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
			return (return_error_s(\
						"get : no such file or directory\nERROR\n\0", -1, SK));
		else if (check_path(f->arr[1], e->ref) == -1)
			return (return_error_s(\
						"get : no such file or directory\nERROR\n\0", -1, SK));
	}
	return (0);
}

int				handle_get(char *cmd, t_env *e)
{
	t_file	f;

	if (check_get(&f, cmd, e) == -1)
		return (-1);
	if ((f.file = open(f.arr[1], O_RDONLY)) > 0)
	{
		while ((f.r = read(f.file, f.buf, BUFSIZE)) != EOF)
		{
			if (f.r < 0)
				exit_error("Erorr reading buf");
			write(SK, f.buf, f.r);
			ft_bzero(f.buf, BUFSIZE);
			if (f.r != BUFSIZE)
				break ;
			f.r = 0;
		}
		close(f.file);
	}
	else
		write(SK, "get : no such file or directory\nERROR\n\0", 39);
	if (f.namefile)
		free(f.namefile);
	return (0);
}

static int		check_put(t_file *f, char *cmd, t_env *e)
{
	f->namefile = get_cmd(cmd);
	if (!f->namefile || check_ifdirexist(f->namefile) >= 0)
	{
		write(SK, "put : file already exist.\nERROR\n\0", 33);
		return (-1);
	}
	if ((f->file = open(f->namefile, O_WRONLY | O_CREAT, S_IRUSR | \
					S_IWUSR)) < 0)
	{
		return (return_error_s(\
					"put : can't open the file.\nERROR\n\0", -1, SK));
	}
	return (0);
}

int				handle_put(char *cmd, t_env *e)
{
	t_file	f;

	init_file(&f);
	if (check_put(&f, cmd, e) == -1)
		return (-1);
	while ((f.r = read(SK, f.buf, BUFSIZE)) >= 0)
	{
		write(f.file, f.buf, f.r);
		if (ft_strsearch(f.buf, "ERROR\n\0"))
			write(SK, "put : no such file or directory.\nERROR\n\0", 40);
		else if (f.r <= 0)
		{
			write(SK, "Socket disconected.\nERROR\n\0", 27);
			break ;
		}
		else if (f.r < BUFSIZE)
		{
			write(SK, "Uplodad completed.\nSUCCESS\n\0", 28);
			break ;
		}
		ft_bzero(f.buf, BUFSIZE);
	}
	close(f.file);
	return (0);
}
