/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:06:15 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/23 18:25:31 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

static char		**create_tab(char *str)
{
	char **tab;
	char *tmp;

	if (!str)
		return (NULL);
	tmp = NULL;
	tab = NULL;
	tmp = ft_strtrim(str);
	tab = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	return (tab);
}

static char		*check_localfile(char *cmd)
{
	char	*namefile;
	char	**arr;

	arr = NULL;
	namefile = NULL;
	arr = create_tab(cmd);
	if (ft_arraylen(arr) == 2)
	{
		namefile = ft_str_last_slash(arr[1]);
		return (namefile);
	}
	else if (ft_arraylen(arr) >= 3)
	{
		namefile = arr[2];
		return (namefile);
	}
	return (NULL);
}

static void		init_get(t_file *f, char *cmd, int check)
{
	f->cmp = 0;
	f->r = 0;
	f->namefile = NULL;
	f->arr = NULL;
	if (check == 1)
		f->arr = create_tab(cmd);
	ft_bzero(f->buf, BUFSIZE);
}

int				handle_get(char *cmd, t_env *e)
{
	t_file f;

	init_get(&f, cmd, 0);
	f.namefile = check_localfile(cmd);
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	while ((f.r = read(e->socketid, f.buf, BUFSIZE)) != EOF)
	{
		f.cmp++;
		if (f.r < 0)
			exit_error("Erorr reading buf");
		if (ft_strsearch(f.buf, "ERROR\n"))
			return (return_error(f.buf));
		else if (ft_strsearch(f.buf, "SUCCESS\n"))
			break ;
		if ((f.cmp == 1) && (f.file = open(f.namefile,\
								O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
			return (return_error("ERROR can't open the file"));
		if (core_get(&f) == -42)
			break ;
	}
	close(f.file);
	ft_putstr("File written. \nSUCCESS\n\0");
	return (1);
}

int				handle_put(char *cmd, t_env *e)
{
	t_file	f;

	init_get(&f, cmd, 1);
	ft_bzero(f.buf, BUFSIZE);
	if (f.arr[1] && (f.file = open(f.arr[1], O_RDONLY)) > 0)
	{
		if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
			return (return_error("Socket disconnected.\n\0"));
		read(SK, f.buf, BUFSIZE);
		if (ft_strsearch(f.buf, "ERROR\n\0"))
			return (return_error(f.buf));
		while ((f.r = read(f.file, f.buf, BUFSIZE)) != EOF)
			if (core_put(SK, &f) == -42)
				break ;
	}
	else
		return (return_error("put : no such file or directory\n\0"));
	close(f.file);
	return (1);
}
