/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:02:21 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/14 22:25:09 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int handle_get(char *cmd, t_env *e)
{
    int r;
    char buf[BUFSIZE];
    int file;
	char **arr;
	char *tmp;

	tmp = NULL;
	arr = NULL;
	arr = ft_strsplit(ft_strtrim(cmd), ' ');
    ft_putendl("ft_get");
    ft_bzero(buf,BUFSIZE);
    r = 0;
	tmp = ft_strdellastslash(cmd);
    if (check_path(tmp, "/Users/nidzik/Documents/ft_p/") == -1 )
	{
		write(SK,"get : no such file or directory\nERROR\n\0",39);
		return (0);
	}
	if ((file = open(arr[1], O_RDONLY)) > 0)
{
        while (( r  = read(file, buf,BUFSIZE)) != EOF)
            {
            if (r < 0)
                exit_error("Erorr reading buf");
            write(SK, buf, r);
            ft_bzero(buf,BUFSIZE);
            if (r != BUFSIZE)
                break;
            r = 0;
        }
			close(file);
    }
	else
		write(SK,"ERROR\n\0",5);
	if (tmp)
		free(tmp);
	return (0);
}

int handle_put(char *cmd, t_env *e)
{
    int file;
    int r;
    char buf[BUFSIZE];
    char *namefile;

    namefile = ft_strtrim(ft_str_sub_until(cmd, 4));
  ft_putendl(namefile);
    if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_WRONLY | O_CREAT, S_IRUSR | \
S_IWUSR)) < 0 )
    {
        ft_putendl("ERROR can't open the file");
        return(1);
    }
    ft_bzero(buf,BUFSIZE);
	write(SK,"OK\0",3);
    ft_putchar('.');
	while ((r = read(SK, buf, BUFSIZE)) >= 0 )
	write(file, buf, r);
	if (r < 0)
	ft_putendl("eror read ");
    close(file);
    ft_putendl("closing file oklm");
	return (0);
}
