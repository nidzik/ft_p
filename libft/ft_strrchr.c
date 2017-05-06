/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 13:01:29 by nidzik            #+#    #+#             */
/*   Updated: 2014/12/17 12:45:05 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int save;

	save = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			save = i;
		i++;
		if (s[i] == (char)c)
			save = i;
	}
	if (save != -1)
		return ((char *)&s[save]);
	return (0);
}
