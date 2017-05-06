/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 10:37:34 by nidzik            #+#    #+#             */
/*   Updated: 2014/12/11 10:51:49 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old, size_t size)
{
	void	*new;

	if (ptr == NULL)
		return (NULL);
	if (size == 0)
		new = (void *)ft_memalloc(sizeof(char));
	else
		new = (void *)ft_memalloc(size);
	if (new == NULL)
		ft_bzero(new, (size) ? size : sizeof(char));
	if (old > size)
		ft_memcpy(new, ptr, (size) ? size : sizeof(char));
	else
		ft_memcpy(new, ptr, old);
	ft_memdel((void *)&ptr);
	return (new);
}
