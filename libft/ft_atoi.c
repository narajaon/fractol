/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 15:48:39 by narajaon          #+#    #+#             */
/*   Updated: 2017/05/20 14:34:13 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_space(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\f'\
			|| str[i] == '\v' || str[i] == '\r')
		i++;
	return (i);
}

int				ft_atoi(const char *str)
{
	int i;
	int nb;
	int temp;
	int neg;

	nb = 0;
	temp = 0;
	neg = 1;
	i = check_space(str);
	if (str[i] == '-')
	{
		neg = -neg;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = temp + str[i] - '0';
		temp = nb * 10;
		i++;
	}
	return (nb * neg);
}
