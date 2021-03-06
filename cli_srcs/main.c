/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 12:05:23 by nidzik            #+#    #+#             */
/*   Updated: 2018/04/02 15:12:40 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

static void		init_env(t_env *e, char **av)
{
	e->port = ft_atoi(av[2]);
	e->socketid = 0;
	e->serv = gethostbyname(av[1]);
	e->ref_path = NULL;
	if (e->serv == NULL)
	{
		ft_putendl("Cannot connect to the host\nERROR\0");
		free(e);
		exit(0);
	}
	ft_bzero(&e->serv_sock, sizeof(e->serv_sock));
	e->serv_sock.sin_family = PF_INET;
	e->serv_sock.sin_addr.s_addr = inet_addr(av[1]);
	ft_memcpy(&e->serv_sock.sin_addr.s_addr, e->serv->h_addr,\
			e->serv->h_length);
	e->serv_sock.sin_port = htons(e->port);
}

static void		connect_to_socket(t_env *e)
{
	if ((e->socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		exit_error("Error while opening the socket.. Exiting");
	if (connect(e->socketid, (struct sockaddr *)&e->serv_sock,\
				sizeof(e->serv_sock)) < 0)
	{
		exit_error("Error while connecting the socket.");
	}
	ft_putendl("Welcome");
}

int				check_cmd(char *cmd, t_env *e)
{
	char		buf[128];
	int			ret;
	char		*tri;

	ret = 0;
	tri = NULL;
	ft_bzero(buf, 128);
	if (ft_strncmp("get ", cmd, 4) == 0)
		return (handle_get(cmd, e) == -1);
	else if (ft_strncmp("put ", cmd, 4) == 0)
	{
		if (handle_put(cmd, e) == -1)
			return (-1);
	}
	else if (ft_strncmp("quit\0", tri = ft_strtrim(cmd), 5) == 0)
	{
		ft_strdel(&tri);
		handle_quit(cmd, e);
	}
	else
		ret = handle_rest(cmd, e);
	ft_strdel(&tri);
	if (ret != -1 && read(SK, buf, BUFSIZE) > 0)
		ft_putstr(buf);
	return (0);
}

static void		send_cmd_and_receive(t_env *e)
{
	int			r;
	char		buf[BUFSIZE];
	int			cmp;

	init_snd_rcve(&cmp, &r);
	ft_bzero(buf, BUFSIZE);
	while (1)
	{
		while ((r = read(0, buf, BUFSIZE)) >= 0)
		{
			snd_rcve_cmd(&cmp, buf, e, r);
			write(1, "\x1B[32mftp> \x1B[0m", 14);
			if (r < BUFSIZE && r > 0)
			{
				ft_bzero(buf, BUFSIZE);
				r = 0;
				break ;
			}
			else
				handle_error_snd_rcve(r, e);
			ft_bzero(buf, BUFSIZE);
			r = 0;
		}
		cmp = 0;
	}
}

int				main(int ac, char **av)
{
	t_env	*e;

	if (ac < 3)
		exit_error("usage ./client hostname port\n");
	e = (t_env *)malloc(sizeof(t_env));
	init_env(e, av);
	connect_to_socket(e);
	login(e);
	send_cmd_and_receive(e);
	ft_putendl("Closing");
	free(e);
	return (0);
}
