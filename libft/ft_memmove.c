/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 11:12:30 by nidzik            #+#    #+#             */
/*   Updated: 2015/03/10 13:02:44 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	void		*ptr;

	d = dst;
	s = src;
	ptr = dst;
	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
	{
		d += len;
		s += len;
		while (len--)
		{
			*--d = *--s;
		}
	}
	return (ptr);
}
