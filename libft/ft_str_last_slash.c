/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_last_slash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 12:19:26 by nidzik            #+#    #+#             */
/*   Updated: 2018/03/17 16:14:02 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_str_last_slash(char *str)
{
	char *ptr;
	char *save;
	int i = 0;
	if (str == NULL)
		return (NULL);
	else if (ft_strchr(str, '/') == NULL)
		return (str);
	save = str;
	ptr = NULL;
	while (*str)
	{
		if (*str == '/' && *(str+1) && *(str+1) != '\0')
		{
			while (str[i] == '/')
			{
				if (str[i+1] && str[i+1] == '\0')
					return ptr;
				else
					i++;
			}
			i = 0;
			ptr = str+1;
		}
		str++;

	}
	str = save;
	return (ptr);
}
