/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:08:47 by mdziadko          #+#    #+#             */
/*   Updated: 2024/12/22 21:48:56 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The strdup() function allocates sufficient memory for a copy of the string 
	s1, does the copy, and returns a pointer to it. The pointer may subsequently
	be used as an argument to the function free(3).
*/

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		len;
	int		i;

	len = ft_strlen(src);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
