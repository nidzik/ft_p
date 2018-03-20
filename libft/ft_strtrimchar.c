/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:58:32 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/20 20:13:30 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strtrimchar(char *s, char o)
{
	int				d;
	unsigned int	c;
	int				start;
	char			*new;

	d = 0;
	c = 0;
	start = 0;
	new = ft_strnew(ft_strlen(s));
	while (c < ft_strlen(s))
	{
		if (!start && s[c] == o)
			c++;
		else
		{
			start = 1;
			new[d++] = s[c++];
		}
	}
	d--;
	while (new[d] == o)
		new[d--] = '\0';
	return (new);
}
