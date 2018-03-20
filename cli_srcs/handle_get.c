/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:06:15 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/20 20:17:32 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

static char *check_localfile(char *cmd)
{
    char *namefile;
    char **arr;
	
    arr = NULL;
	namefile = NULL;
    arr = ft_strsplit(ft_strtrim(cmd), ' ');
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

int	handle_get(char *cmd, t_env *e)
{
	int file;
	int r;
	char buf[BUFSIZE];
	char *namefile;
	int cmp;

	cmp = 0;
	namefile = NULL;
	namefile = check_localfile(cmd);
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	ft_bzero(buf,BUFSIZE);
	while (( r  = read(e->socketid, buf,BUFSIZE)) > 0){
		cmp++;
		if (r < 0)
			exit_error("Erorr reading buf");
		if (ft_strsearch(buf, "ERROR\n"))
        {
			write(1, buf, r);
			return (-1);
		}
		if ((cmp == 1) && (file = open(ft_strtrim(namefile),			\
								 O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0 ) 
		{
			ft_putendl("ERROR can't open the file");
			return (-1);
		}

		write(file, buf, r);
		ft_bzero(buf,BUFSIZE);
		if (r != BUFSIZE)
			break;
		r = 0;
	}
	close(file);
	ft_putstr("File written. \nSUCCESS\n\0");
	return (1);
}


int	handle_put(char *cmd, t_env *e)
{
   int r;
    char buf[BUFSIZE];
//	char rep[3];
    int file;
	char **tab;

	tab = NULL;
	tab = ft_strsplit(ft_strtrim(cmd), ' ');
    ft_bzero(buf,BUFSIZE);
    r = 0;
    if (tab[1] && (file = open(tab[1], O_RDONLY)) > 0)
		{
			if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
				ft_putendl("Socket disconnected.");
//			if (read(SK,rep,3 ) < 0)
//				exit_error("Error, can't read on the socket.");
			read(SK, buf, BUFSIZE);
			if (ft_strsearch(buf, "ERROR\n\0"))
			{
				write(1, buf, ft_strlen(buf));
				return (-1);
			}
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
		}
	else
	{
//		write(SK, "ERROR\n\0", 7);
		ft_putstr("put : no such file or directory\n\0");
		return (-1);
	}
	close(file);	
	return (1);
}
