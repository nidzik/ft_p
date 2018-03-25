/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:24:02 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/25 18:00:31 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	exit_error(char *err)
{
	ft_putendl(err);
	exit(1);
}

int		return_error_s(char *err, int i, int sk)
{
	write(sk, err, ft_strlen(err) + 1);
	return (i);
}

int		error_cmd_cd(int sk, char *cmd, char *erorr, char *args)
{
	if (args == NULL || ft_strcmp(args, "") == 0)
		write(sk, "Usage : cd <PATH>\nERROR\n\0", 25);
	else
		write(sk, "cd : No such file or directory\nERROR\n\0", 38);
	(void)cmd;
	(void)erorr;
	return (-1);
}

char	*get_cmd(char *cmd)
{
	char *str;
	char **tab;
	char *tmp;

	if (!cmd)
		return (NULL);
	tab = NULL;
	str = NULL;
	tmp = NULL;
	tmp = ft_strtrim(cmd);
	tab = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	if (tab[1])
	{
		str = ft_strdup(tab[1]);
		ft_arraydel(tab);
		return (str);
	}
	else
	{
		ft_arraydel(tab);
		return (NULL);
	}
}

char	**create_tab(char *str)
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
