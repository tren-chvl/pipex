/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:19:27 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:38 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_hexa_unsigned(unsigned int nb, int uppercase)
{
	int		count;
	char	tab;
	char	*base;

	count = 0;
	if (!uppercase)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb >= 16)
		count += ft_hexa_unsigned(nb / 16, uppercase);
	tab = base[nb % 16];
	count += write(1, &tab, 1);
	return (count);
}
