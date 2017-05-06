/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:47:15 by nidzik            #+#    #+#             */
/*   Updated: 2014/11/11 15:54:50 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;
	int	k;

	k = n;
	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return ((char *)s1);
	while (k != 0 && s1[i])
	{
		if (s1[i] == s2[j])
			j++;
		else
		{
			i = i - j;
			j = 0;
			k = n - i;
		}
		k--;
		i++;
		if (s2[j] == '\0')
			return ((char *)&s1[i - j]);
	}
	return (0);
}
