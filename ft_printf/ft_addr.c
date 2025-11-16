/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:13:00 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:10 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_convert(unsigned long str)
{
	char	tab;
	int		count; 

	count = 0;
	if (str >= 16)
	{
		count += ft_convert(str / 16);
	}
	tab = "0123456789abcdef"[str % 16];
	count += write(1, &tab, 1);
	return (count);
}

int	ft_addr(void *ptr)
{
	unsigned long	str;
	int				count;

	if (!ptr)
		return (0);
	count = 0;
	str = (unsigned long)ptr;
	count += ft_putstr("0x");
	count += ft_convert(str);
	return (count);
}
