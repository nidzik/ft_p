/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 11:02:01 by nidzik            #+#    #+#             */
/*   Updated: 2015/03/10 16:08:14 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s1, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new_str;

	i = 0;
	if ((len + start) <= ft_strlen(s1) && s1)
	{
		new_str = (char *)malloc(sizeof(char) * len + 1);
		if (new_str == NULL)
			return (NULL);
		while (i < (len + start))
		{
			if (i >= start)
				new_str[i - start] = s1[i];
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	else
		return (NULL);
}
