/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 08:31:34 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/17 09:27:45 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **ast, void (*del)(void *, size_t))
{
	t_list *ptr;
	t_list *ptr2;

	ptr = *ast;
	ptr2 = NULL;
	while (ptr)
	{
		ptr2 = ptr->next;
		del(ptr->content, ptr->content_size);
		free(ptr);
		ptr = ptr2;
	}
	*ast = 0;
}
