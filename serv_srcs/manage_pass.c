/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:52:01 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/21 18:36:36 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_pass(char *pass, int sockid)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open(".pass", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		write(sockid, "Cannot create pass\nERROR\n\0", 26);
		return (-1);
	}
	str = crypt(pass, "1234");
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		write(sockid, "Cannot create pass\nERROR\n\0", 26);
		close(fd);
		return (-1);
	}
	close(fd);
	write(sockid, "Password created.\nSUCCESS\n\0", 28);
	return (1);
}

int		verify_pass(char *pass, int sockid)
{
	int		fd;
	char	pass_file[256];
	char	*dec;

	dec = NULL;
	ft_bzero(pass_file, 256);
	fd = open(".pass", O_RDONLY);
	if (fd == -1)
	{
		write(sockid, "Cannot check pass\nERROR\n\0", 25);
		return (-1);
	}
	if (read(fd, pass_file, 256) == -1)
		return (-1);
	dec = crypt(pass, "1234");
	if (!ft_strncmp(dec, pass_file, ft_strlen(dec)))
	{
		write(sockid, "Connected\nSUCCESS\n\0", 19);
		return (1);
	}
	else
	{
		write(sockid, "Wrong password\nERROR\n\0", 22);
		return (-1);
	}
}
