#include "ft_p_cli.h"

static void init_env(t_env *e, char **av)
{
	e->port = ft_atoi(av[2]);
	e->socketid = 0;
	e->serv = gethostbyname(av[1]);
	if (e->serv == NULL)
    {
		ft_putendl("No such ho");
		exit(0);
    }
	ft_bzero(&e->serv_sock, sizeof(e->serv_sock));
	e->serv_sock.sin_family = PF_INET;
	// IF is not 127.0.0.1 but "localhost" do memcpy else do inet
	//  ft_memcpy(&e->serv_sock.sin_addr.s_addr, e->serv->h_addr, e->serv->h_length);
	e->serv_sock.sin_addr.s_addr = inet_addr(av[1]);
	//e->serv_sock.sin_addr.s_addr = htons(e->serv->h_addr);
	e->serv_sock.sin_port = htons(e->port);
}

static void connect_to_socket(t_env * e)
{
	if ((e->socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		exit_error("Error while opening the socket.. Exiting");
	if (connect(e->socketid,(struct sockaddr *)&e->serv_sock,sizeof(e->serv_sock)) < 0)
		exit_error("Error while connecting the socket, if your using localhost try 127.0.0.1");
	ft_putendl("Welcome");
}

static int check_cmd(char *cmd, t_env *e)
{
	char	buf[128];

	int ret ;
	ret = 0;
	ft_bzero(buf, 128);
	if (ft_strncmp("get", cmd, 3) == 0)
	{
		handle_get(cmd, e);
		return(1); // care
	}
	else if (ft_strncmp("put", cmd, 3) == 0)
	{
		handle_put(cmd, e);
		return(1); // careful 
	}
	else if (ft_strequ("quit", cmd) == 1)
		handle_quit(cmd, e);
	else
		ret = handle_rest(cmd,e);
	if (ret != -1 && read(SK, buf, BUFSIZE) > 0)
	{
		ft_putstr(buf);
		return 0 ;
	}
	return (0);
}

static void send_cmd_and_receive(t_env *e)
{
	int r;
	char buf[BUFSIZE];
	int i;

	ft_bzero(buf,BUFSIZE);
	r = 0;
	i = 0;
	write(1,"\x1B[32mftp> \x1B[0m",14);
	while ((r = read(0, buf, BUFSIZE)) > 0)
	{
		
		buf[r] = '\0';
		if (ft_strlen(buf) > 1)
		{
			ft_putendl("fck_U_good");
			(check_cmd(buf, e));
		}
		r = 0;
		write(1,"\x1B[32mftp> \x1B[0m",14);
	}
}

int main(int ac, char **av)
{
	t_env *e;

	if (ac < 3)
		exit_error("usage ./client hostname port\n");
	e = (t_env *)malloc(sizeof(t_env));
	init_env(e, av);
	connect_to_socket(e);
	send_cmd_and_receive(e);
	ft_putendl("Closing");  
	return(0);
}
