/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:37:21 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/14 11:07:08 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*ptr;
	int		i;

	i = 0;
	if (!(str = ft_strnew(len)))
		return (NULL);
	ptr = (char *)s;
	while (len)
	{
		str[i++] = ptr[start++];
		len--;
	}
	return (str);
}
