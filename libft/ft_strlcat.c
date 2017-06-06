/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:09:25 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/17 11:33:37 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*ptr;
	size_t	val;

	ptr = dst;
	val = ft_strlen(dst) + ft_strlen((char *)src);
	if (size < ft_strlen(dst))
		return (ft_strlen((char *)src) + size);
	while (*ptr && size)
	{
		ptr++;
		size--;
	}
	if (!size)
		return (val);
	while (size > 1 && *src)
	{
		*ptr++ = *src++;
		size--;
	}
	*ptr = '\0';
	return (val);
}
