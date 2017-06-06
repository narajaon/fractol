/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:28:14 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/14 11:03:46 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*ptr;
	int		i;

	i = 0;
	if (!(str = ft_strnew(ft_strlen(s))))
		return (NULL);
	ptr = (char *)s;
	while (ptr[i])
	{
		str[i] = f(ptr[i]);
		i++;
	}
	return (str);
}
