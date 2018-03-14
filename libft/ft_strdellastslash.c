/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdellastslash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 21:31:30 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/14 22:01:35 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdellastslash(char *str)
{
	char	*save;
	char	*ptr;
	char	*new;
	int 	j;
	int		i;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	ptr = NULL;
	new = NULL;
	new = ft_strdup(str);
	save = new;
	while (new[i])
	{
		if (new[i] == '/')
			j = i;
		i++;;
	}
	new[j] = '\0';
	return (new);
}
