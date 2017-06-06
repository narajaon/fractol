/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:57:17 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/13 14:15:30 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	int temp;

	temp = 0;
	if (nb == -2147483648)
	{
		nb = nb / 10;
		temp = 8;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
	else if (nb <= 9 && nb >= 0)
		ft_putchar(nb % 10 + '0');
	if (temp != 0)
		ft_putchar(temp + '0');
}
