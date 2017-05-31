/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:23:48 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/25 14:51:28 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	char	*ptr;
	int		i;
	int		i_2;

	i = 0;
	i_2 = 0;
	if (!*s)
		return ((char *)s);
	ptr = (char *)s;
	while ((*ptr == ' ' || *ptr == '\n' || *ptr == '\t') && *ptr)
		ptr++;
	if (!*ptr)
		return (ptr);
	while (ptr[i])
		i++;
	i--;
	while ((ptr[i] == ' ' || ptr[i] == '\n' || ptr[i] == '\t') && ptr[i])
		i--;
	if (!(str = ft_strnew(i - i_2 + 1)))
		return (NULL);
	while (i_2++ <= i)
		str[i_2 - 1] = ptr[i_2 - 1];
	return (str);
}
