/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:11:28 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/14 11:04:16 by narajaon         ###   ########.fr       */
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

static int		check_str(const char *str, const char *to_find, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == to_find[j] && str[i] && to_find[j])
	{
		i++;
		j++;
	}
	if (j == len)
		return (1);
	return (0);
}

char			*ft_strstr(const char *str, const char *to_find)
{
	char	*temp;
	int		len;

	len = 0;
	temp = (char *)str;
	if (!(ft_strcmp(to_find, "")) && !(ft_strcmp(str, "")))
		return ((char *)str);
	if (check_len(str, to_find))
		return (0);
	if (!to_find)
		return ((char *)str);
	while (to_find[len])
		len++;
	while (*str)
	{
		if (check_str(str, to_find, len))
			return ((char *)str);
		str++;
	}
	return (0);
}
