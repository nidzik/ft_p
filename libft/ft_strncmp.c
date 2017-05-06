/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:38:04 by nidzik            #+#    #+#             */
/*   Updated: 2015/03/10 13:23:57 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[i]) && n != 0)
	{
		n--;
		if (n == 0 || s2[i] == '\0')
			return ((int)(s1[i] - s2[i]));
		i++;
	}
	if (s1[i] == '\200' && s2[i] == '\0')
		return ((int)(s2[i] - s1[i]));
	return ((int)(s1[i] - s2[i]));
}
