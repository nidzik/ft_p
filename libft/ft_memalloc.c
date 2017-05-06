/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 10:34:49 by nidzik            #+#    #+#             */
/*   Updated: 2014/12/11 10:50:31 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memalloc(size_t size)
{
	char			*memory;
	unsigned int	cpt;
	char			*expl;

	memory = malloc(size);
	if (memory != NULL)
	{
		expl = (char *)memory;
		cpt = 0;
		while (cpt++ < size)
			*expl++ = 0;
	}
	return (memory);
}
