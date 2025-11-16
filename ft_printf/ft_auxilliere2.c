/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auxilliere2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:18:20 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:36 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	pourcentage_addr(va_list args)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (ft_putstr("(nil)"));
	return (ft_addr(ptr));
}

int	pourcentage_x(va_list args, int uppercase)
{
	unsigned int	nb;

	nb = va_arg(args, unsigned int);
	return (ft_hexa_unsigned(nb, uppercase));
}
