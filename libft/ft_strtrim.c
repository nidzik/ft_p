/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 11:12:42 by nidzik            #+#    #+#             */
/*   Updated: 2015/03/10 16:08:56 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s)
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
		if (!start && (s[c] == ' ' || s[c] == '\t' || s[c] == '\n'))
			c++;
		else
		{
			start = 1;
			new[d++] = s[c++];
		}
	}
	d--;
	while (new[d] == ' ' || new[d] == '\t' || new[d] == '\n')
		new[d--] = '\0';
	return (new);
}
