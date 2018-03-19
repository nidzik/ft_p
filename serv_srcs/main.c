/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:30:45 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/19 19:05:56 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void init_env(t_env *e, char **av)
{
	e->port = ft_atoi(av[1]);
	e->prot = getprotobyname("tcp");
	e->socketid = 0;
	e->ref = NULL;
	e->accept_socket = 0;
	e->pid = 0;
	e->cli_size = 0;
	ft_bzero(&e->serv_sock, sizeof(e->serv_sock));
	e->serv_sock.sin_family  = AF_INET;
	e->serv_sock.sin_port = htons(e->port);
	e->serv_sock.sin_addr.s_addr = htonl(INADDR_ANY);
  
}

static void sock_bind_listen(t_env *e)
{
	if ((e->socketid = socket(PF_INET, SOCK_STREAM, e->prot->p_proto)) < 0)
		exit_error("socket error server side.\nExiting...");
	if ((bind(e->socketid, (struct sockaddr *) &e->serv_sock, sizeof(e->serv_sock))) < 0)
		exit_error("Error while binding the socket.\nExiting...");
	if (listen(e->socketid, 5) < 0 )
		exit_error("Error while listing. Exiting...");  
}

static void ft_ftp(t_env *e)
{
	int req;
	int r;
	char buf[128];
  
	req = 0;
	ft_putendl("Reading the cmd from socket...");
	while(42)
		if ((r = read(SK, (char *)buf, sizeof(buf))) >0)
		{
			if (r <= 0)
				exit_error("Error while readding ");
			if (r > 127)
				buf[127] = '\0';
			else
				buf[r] = '\0';
				get_fct(buf, e);
            ft_bzero(buf, 128);
			req = 0;
			r = 0;
		}
		else
			break;
}

static void boucle_accept(t_env *e)
{
	while(42)
    {
		if ((e->accept_socket = accept(e->socketid, (struct sockaddr *) &e->cli_sock, (unsigned int *)&e->cli_size)) < 0)
			exit_error("Error while accepting the socket. Exiting...");
		if ((e->pid = fork()) == 0)
		{
			close(e->socketid);
			//handle
			if (connect_me(e->accept_socket, e) != 1)
				;
			ft_ftp(e);
			close(e->accept_socket);
			exit(0);
		}
    }
}

int main(int ac, char **av)
{
	t_env *e;
  
	if (!(e = (t_env *)malloc(sizeof(t_env))))
		exit_error("Error : malloc fail");
	if (ac < 2)
		exit_error("usage ./server port");
	init_env(e, av);
	sock_bind_listen(e);
	boucle_accept(e);
	return(0);
}

