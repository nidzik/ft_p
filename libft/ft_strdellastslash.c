/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdellastslash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:31:30 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/23 19:30:33 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdellastslash(char *str)
{
	char	*new;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (str == NULL || ft_strchr(str, '/') == 0)
		return (NULL);
	new = NULL;
	new = ft_strdup(str);
	while (new[i])
	{
		if (new[i] == '/')
			j = i;
		i++;
	}
	new[j] = '\0';
	return (new);
}
