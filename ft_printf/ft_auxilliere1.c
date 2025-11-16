/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auxilliere1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:17:08 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:33 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	pourcentage_c(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	return (write(1, &c, 1));
}

int	pourcentage_double(void)
{
	return (write(1, "%", 1));
}

int	pourcentage_int(va_list args)
{
	int	nb;

	nb = va_arg(args, int);
	return (ft_putnbr(nb));
}

int	pourcentage_s(va_list args)
{
	char	*s;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	return (ft_putstr(s));
}
