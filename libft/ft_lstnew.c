/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 14:27:48 by narajaon          #+#    #+#             */
/*   Updated: 2017/05/25 13:59:48 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ll;

	if (!(ll = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == (void *)0)
	{
		ll->content = (void *)0;
		ll->content_size = 0;
	}
	else
	{
		if (!(ll->content = ft_memalloc(content_size)))
		{
			free(ll->content);
			return (NULL);
		}
		ll->content = ft_memcpy(ll->content, content, content_size);
		ll->content_size = content_size;
	}
	ll->next = NULL;
	return (ll);
}
