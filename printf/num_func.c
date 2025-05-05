/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:46:19 by mdziadko          #+#    #+#             */
/*   Updated: 2025/02/17 17:49:53 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_nbr(long n, int *count)
{
	if (n < 0)
	{
		if (put_char('-', count) < 0)
			return (-1);
		n = -n;
	}
	if (n >= 10)
	{
		if (put_nbr((n / 10), count) < 0)
			return (-1);
	}
	return (put_char(n % 10 + '0', count));
}

int	put_udec(unsigned int n, int *count)
{
	if (n >= 10)
	{
		if (put_udec((n / 10), count) < 0)
			return (-1);
	}
	return (put_char(n % 10 + '0', count));
}

int	put_hex(unsigned long n, int is_up, int *count)
{
	char	*hex;

	if (is_up)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (n >= 16)
	{
		if (put_hex((n / 16), is_up, count) < 0)
			return (-1);
	}
	return (put_char(hex[n % 16], count));
}
