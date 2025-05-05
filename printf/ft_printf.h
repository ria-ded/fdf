/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:53:07 by mdziadko          #+#    #+#             */
/*   Updated: 2025/04/23 21:56:05 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

void	find_function(char specifier, va_list *args, int *count);
int		ft_printf(const char *str, ...);
int		put_char(int c, int *count);
int		put_str(const char *str, int *count);
int		put_nbr(long n, int *count);
int		put_udec(unsigned int n, int *count);
int		put_hex(unsigned long n, int is_up, int *count);
int		put_ptr(void *ptr, int *count);

#endif