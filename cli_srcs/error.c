/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:44:39 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/23 18:56:52 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_cli.h"

void	exit_error(char *err)
{
	ft_putendl(err);
	exit(1);
}

int		return_error(char *str)
{
	ft_putstr(str);
	return (-1);
}

void	zeroo(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

void	uno(t_file *f)
{
	f->cmp = 1;
	f->r = 0;
}
