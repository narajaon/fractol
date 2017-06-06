/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 11:49:07 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/14 13:42:53 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		base_len(long n)
{
	if (n < 10)
		return (1);
	return (base_len(n / 10) + 1);
}

static char		*to_asci(char *str, long n)
{
	if (n >= 10)
	{
		to_asci(str, n / 10);
		to_asci(str, n % 10);
	}
	if (n < 10)
	{
		while (*str)
			str++;
		*str = n + '0';
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char *str;
	long len;

	len = (n < 0) ? -(long)n : (long)n;
	len = base_len(len);
	len = (n < 0) ? len + 1 : len;
	if (!(str = ft_strnew(len)))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	len = (n < 0) ? -(long)n : (long)n;
	to_asci(str, len);
	return (str);
}
