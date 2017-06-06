/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:50:40 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/14 10:05:16 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_len(const char *str, const char *to_find)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (to_find[j])
		j++;
	if (j > i)
		return (1);
	return (0);
}

static int		check_str(const char *str, const char *to_find, int len, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == to_find[j] && str[i] && to_find[j] && n)
	{
		i++;
		j++;
		n--;
	}
	if (j == len)
		return (1);
	return (0);
}

char			*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	char	*temp;
	int		len;

	len = 0;
	temp = (char *)str;
	if (check_len(str, to_find))
		return (0);
	if (!(to_find))
		return ((char *)str);
	while (to_find[len])
		len++;
	while (n)
	{
		if (check_str(str, to_find, len, n))
			return ((char *)str);
		str++;
		n--;
	}
	return (0);
}
