/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iota.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 10:21:05 by nidzik            #+#    #+#             */
/*   Updated: 2015/08/22 20:13:02 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*resstring;

	resstring = ft_strnew(20);
	if (n >= 0 && resstring)
	{
		*--resstring = '0' + (n % 10);
		n /= 10;
		while (n != 0)
		{
			*--resstring = '0' + (n % 10);
			n /= 10;
		}
	}
	else if (resstring)
	{
		*--resstring = '0' - (n % 10);
		n /= 10;
		while (n != 0)
		{
			*--resstring = '0' - (n % 10);
			n /= 10;
		}
		*--resstring = '-';
	}
	return (resstring);
}
