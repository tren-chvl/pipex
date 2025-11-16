/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:26:39 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:44 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_put(unsigned int nb)
{
	int		count;
	char	c;

	count = 0;
	if (nb > 9)
		count += ft_put(nb / 10);
	c = '0' + (nb % 10);
	count += write(1, &c, 1);
	return (count);
}

int	pourcentage_u(va_list args)
{
	unsigned int	u;

	u = va_arg(args, unsigned int);
	return (ft_put(u));
}
