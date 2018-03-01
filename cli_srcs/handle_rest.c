/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 21:27:11 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/01 23:55:29 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

int handle_rest(char *cmd, t_env *e)
{
	int r;
    char buf[BUFSIZE];
	
	if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	ft_bzero(buf,BUFSIZE);
	r = 0;
	if (( r  = read(e->socketid, buf,BUFSIZE)) > 0){
		if (r <= 0)
			exit_error("Erorr reading buf");
		if (r < BUFSIZE - 1 )
			buf[r] = '\0';
		ft_putstr(buf);
		if (ft_strsearch(buf, "ERROR\n") || ft_strsearch(buf, "SUCCESS"))
		{
			ft_bzero(buf,BUFSIZE);
			return (-1);
		}
		ft_bzero(buf,BUFSIZE);
	}
	return (1); 
}

void handle_quit(char *cmd, t_env *e)
{	
if (write(e->socketid, cmd, ft_strlen(cmd)) < 0)
		exit_error("Error, can't write on the socket.");
	free(e);
	exit(0);
}
