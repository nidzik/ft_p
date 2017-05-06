/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:13:28 by nidzik            #+#    #+#             */
/*   Updated: 2015/03/10 17:03:45 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(const char *str)
{
	int				signe;
	int				res;
	unsigned int	i;

	i = 0;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' ||
				*str == '\r' || *str == '\f')
		str++;
	signe = (*str == '-' ? -1 : 1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	if (ft_strlen(str) > 19)
		return (signe == 1 ? -1 : 0);
	while (ft_isdigit(*str) && *str != '\0')
	{
		i = (int)(*str - '0');
		res = (res * 10) + i;
		str++;
	}
	return (res * signe);
}
