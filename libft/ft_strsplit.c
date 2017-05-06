/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <bbichero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 11:02:01 by bbichero          #+#    #+#             */
/*   Updated: 2015/03/10 18:07:36 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_str(const char *s, char c)
{
	int		nb_str;
	int		i;

	i = 0;
	nb_str = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			nb_str++;
		}
		s++;
	}
	return (nb_str);
}

static int		ft_length(const char *s, char c)
{
	int			length;

	length = 0;
	while (*s != c && *s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

char			**ft_strsplit(const char *s, char c)
{
	char		**t;
	int			nb_str;
	int			j;

	nb_str = ft_nb_str((const char *)s, c);
	j = 0;
	t = (char **)malloc(sizeof(*t) * (ft_nb_str((const char *)s, c) + 1));
	if (t == NULL)
		return (NULL);
	t[0] = (char *)malloc((sizeof(char) * nb_str) + 1);
	while (nb_str--)
	{
		while (*s == c && *s)
			s++;
		t[j] = ft_strsub((const char *)s, 0, ft_length((const char *)s, c));
		if (t[j] == NULL)
			return (NULL);
		s = s + ft_length(s, c);
		j++;
	}
	t[j] = NULL;
	return (t);
}
