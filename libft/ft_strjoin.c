/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 19:48:46 by nidzik            #+#    #+#             */
/*   Updated: 2014/12/17 12:07:41 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;

	if (!s1 || !s2)
		return ((char *)0);
	dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return ((char *)0);
	ft_strncpy(dst, s1, ft_strlen(s1));
	ft_strncat(dst, s2, ft_strlen(s2));
	return (dst);
}
