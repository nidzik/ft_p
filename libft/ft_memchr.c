/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 12:32:19 by nidzik            #+#    #+#             */
/*   Updated: 2015/03/10 12:18:56 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*str;
	size_t				i;

	i = 0;
	str = s;
	if (n > 0 && s)
	{
		while (i < n)
		{
			if (str[i] == (unsigned char)c)
				return ((char *)&str[i]);
			i++;
		}
	}
	return (NULL);
}
