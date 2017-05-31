/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:14:40 by narajaon          #+#    #+#             */
/*   Updated: 2017/04/17 10:52:25 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
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
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	else if (nb <= 9 && nb >= 0)
		ft_putchar_fd(nb % 10 + '0', fd);
	if (temp != 0)
		ft_putchar_fd(temp + '0', fd);
}
