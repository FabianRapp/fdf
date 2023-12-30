/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle_u.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:36:35 by frapp             #+#    #+#             */
/*   Updated: 2023/12/30 22:00:01 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_handle_u(va_list *arg, int *written_bytes)
{
	char			result[20];
	int				i;
	char			sign;
	unsigned int	n;

	n = va_arg(*arg, unsigned);
	sign = 0;
	i = 19;
	result[i--] = 0;
	if (!n)
		result[i--] = '0';
	while (n)
	{
		result[i--] = '0' + (n % 10);
		n /= 10;
	}
	if (sign)
		result[i--] = '-';
	i++;
	if (write (1, result + i, ft_strlen(result + i)) == -1)
		return (-1);
	*written_bytes += ft_strlen(result + i);
	return (0);
}
