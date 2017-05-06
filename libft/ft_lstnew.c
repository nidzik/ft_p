/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 10:34:14 by nidzik            #+#    #+#             */
/*   Updated: 2014/12/11 10:50:13 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = malloc(1);
	if (new == NULL)
		return (NULL);
	else if (content_size == 0)
		new->content = NULL;
	else if (content == NULL)
	{
		new->content_size = 0;
		new->content = NULL;
	}
	new->content = malloc(sizeof(content));
	if (new->content == NULL)
		new->content_size = content_size;
	new->next = NULL;
	return (new);
}
