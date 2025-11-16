/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:23:12 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:42 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_pourcentage(char c, va_list args)
{
	if (c == 'c')
		return (pourcentage_c(args));
	else if (c == '%')
		return (pourcentage_double());
	else if (c == 'd' || c == 'i')
		return (pourcentage_int(args));
	else if (c == 's')
		return (pourcentage_s(args));
	else if (c == 'p')
		return (pourcentage_addr(args));
	else if (c == 'u')
		return (pourcentage_u(args));
	else if (c == 'x')
		return (pourcentage_x(args, 0));
	else if (c == 'X')
		return (pourcentage_x(args, 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			count;
	int			i;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i])
				count += ft_pourcentage(str[i], args);
			else
				return (count);
		}
		else
		{
			count += write(1, &str[i], 1);
		}
		i++;
	}
	va_end(args);
	return (count);
}
