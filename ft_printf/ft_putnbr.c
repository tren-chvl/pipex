/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:27:13 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:46 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_putnbr(int nb)
{
	int		count;
	char	c;

	count = 0;
	if (nb == -2147483648)
	{
		count = count + write(1, "-2147483648", 11);
		return (count);
	}
	if (nb < 0)
	{
		count = count + write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		count = count + ft_putnbr(nb / 10);
	}
	c = '0' + (nb % 10);
	count = count + write(1, &c, 1);
	return (count);
}
