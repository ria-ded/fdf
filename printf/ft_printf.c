/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:00:25 by mdziadko          #+#    #+#             */
/*   Updated: 2025/02/17 17:49:41 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i] && count >= 0)
	{
		if (str[i] != '%')
			put_char(str[i], &count);
		else
		{
			if (str[i + 1] == '\0')
				break ;
			find_function(str[i + 1], &args, &count);
			i++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

void	find_function(char specifier, va_list *args, int *count)
{
	if (specifier == 'c')
		put_char(va_arg(*args, int), count);
	else if (specifier == 's')
		put_str(va_arg(*args, const char *), count);
	else if (specifier == 'd' || specifier == 'i')
		put_nbr(va_arg(*args, int), count);
	else if (specifier == 'u')
		put_udec(va_arg(*args, unsigned int), count);
	else if (specifier == 'x')
		put_hex((unsigned int)va_arg(*args, unsigned int), 0, count);
	else if (specifier == 'X')
		put_hex((unsigned int)va_arg(*args, unsigned int), 1, count);
	else if (specifier == 'p')
		put_ptr(va_arg(*args, void *), count);
	else
		put_char(specifier, count);
}
