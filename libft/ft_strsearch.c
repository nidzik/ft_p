/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:51:21 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/20 20:14:20 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strsearch(char *src, char *find)
{
	int		i;

	i = 0;
	if (!src || !find)
		return (-1);
	while (*src)
	{
		if (*src == find[i])
		{
			while (find[i] && src[i] == find[i])
				i++;
		}
		if (i == (int)ft_strlen(find))
			return (1);
		else
			i = 0;
		src++;
	}
	return (0);
}
