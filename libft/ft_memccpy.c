/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 19:40:00 by nidzik            #+#    #+#             */
/*   Updated: 2014/12/17 12:03:37 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		ch;

	ch = (unsigned char)c;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (n != 0)
	{
		d[i] = s[i];
		if (d[i] == ch)
			return (d + i + 1);
		i++;
		n--;
	}
	return (NULL);
}
