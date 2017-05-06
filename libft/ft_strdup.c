/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 10:38:10 by nidzik            #+#    #+#             */
/*   Updated: 2014/12/12 10:56:23 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*t;
	int		i;

	i = 0;
	t = (char *)malloc(ft_strlen(s1) * sizeof(char *));
	if (t == NULL)
		return (t);
	while (s1[i] != '\0')
	{
		t[i] = s1[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
