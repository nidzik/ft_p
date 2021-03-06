/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:58:18 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/20 20:03:06 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(char **a)
{
	int		i;

	i = 0;
	while (*a != NULL)
	{
		i++;
		a++;
	}
	return (i);
}

void		ft_print_array(char **arr)
{
	int		i;

	i = 0;
	ft_putnbr(len(arr));
	ft_putendl("Array = {");
	while (arr[i] != NULL)
	{
		ft_putchar('[');
		ft_putstr(arr[i]);
		ft_putchar(']');
		ft_putchar('\n');
		i++;
	}
	if (arr[i] == NULL)
		ft_putendl("NULL");
	ft_putendl("\t}");
	ft_putchar('\n');
}
