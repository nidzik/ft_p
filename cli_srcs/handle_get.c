/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:06:15 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/16 23:23:19 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"
/*
static char *check_localfile(char *cmd)
{
    char *namefile;
    char **arr;
	
    arr = NULL;
	namefile = NULL;
	ft_putendl(cmd);
    arr = ft_strsplit(ft_strtrim(cmd), ' ');
	ft_putendl(arr[1]);
    if (ft_arraylen(arr) == 2)
	{
        namefile = ft_str_last_slash(arr[1]);
		ft_putendl("namefiel1");
		ft_putendl(namefile);
		ft_putendl("namefiel1");
		return (namefile);
	}
    else if (ft_arraylen(arr) >= 3)
	{
        namefile = arr[2];
		ft_putendl("namefiel2");
		return (namefile);
	}
		ft_putendl("namefiel1NULL");
	return (NULL);
}
*/
int	handle_get(char *cmd, t_env *e)
{
	int file;
	int r;
	char buf[BUFSIZE];
	char *namefile;

	namefile = NULL;
	char **arr;

	arr = NULL;
	arr = ft_strsplit(ft_strtrim(cmd), ' ');
	ft_print_array(arr);
	if (ft_arraylen(arr) == 2)
		namefile = ft_str_last_slash(arr[1]);
	else if (ft_arraylen(arr) >= 3)
		namefile = arr[2];
	ft_putchar('-');
	ft_putendl(ft_strtrim(arr[1]));
	ft_putchar('-');
//	namefile = check_localfile(cmd);
//	ft_putendl(namefile);
	if ((file = open(ft_strtrim(namefile), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0 ) 
	{
		ft_putendl("ERROR can't open the file");
		return (-1);
	}
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	ft_bzero(buf,BUFSIZE);
	ft_putendl("enter read get");
	while (( r  = read(e->socketid, buf,BUFSIZE)) > 0){
		if (r < 0)
			exit_error("Erorr reading buf");
		if (ft_strsearch(buf, "ERROR\n"))
        {
			write(1, buf, r);
			break;
		}
		write(file, buf, r);
		ft_bzero(buf,BUFSIZE);
		if (r != BUFSIZE)
			break;
		r = 0;
	}
	ft_putendl("enter read get");
	close(file);
	ft_putendl("closing file oklm");
	return (1);
}


int	handle_put(char *cmd, t_env *e)
{
   int r;
    char buf[BUFSIZE];
//	char rep[3];
    int file;

	ft_putendl(cmd);
	ft_putchar('-');
    ft_putendl(ft_strtrim(ft_str_sub_until(cmd, 4)));
	ft_putchar('-');
    ft_bzero(buf,BUFSIZE);
    r = 0;
    if ((file = open(ft_strtrim(ft_str_sub_until(cmd, 4)), O_RDONLY)) > 0)
		{
			if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
				ft_putendl("Socket disconnected.");
//			if (read(SK,rep,3 ) < 0)
//				exit_error("Error, can't read on the socket.");
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
		ft_putendl("error open file");
		return (0);
	}
	close(file);	
	return (1);
}
