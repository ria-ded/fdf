/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:39:30 by mdziadko          #+#    #+#             */
/*   Updated: 2025/04/23 21:46:53 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_char(int c, int *count)
{
	int	res;

	res = write(1, &c, 1);
	if (res < 0)
		*count = -1;
	else
		*count += res;
	return (*count);
}

int	put_str(const char *str, int *count)
{
	int	res;

	if (!str)
		str = "(null)";
	res = write (1, str, ft_strlen(str));
	if (res < 0)
		*count = -1;
	else
		*count += res;
	return (*count);
}

int	put_ptr(void *ptr, int *count)
{
	if (!ptr)
		return (put_str("(nil)", count));
	if (put_str("0x", count) < 0)
		return (-1);
	return (put_hex((unsigned long)ptr, 0, count));
}
