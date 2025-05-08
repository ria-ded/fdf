/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:11:56 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/05 17:44:38 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	hex_to_int(char *hex)
{
	char	*base;
	int		res;
	int		i;
	char	c;

	if (!hex)
		return (-1);
	base = "0123456789abcdef";
	res = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;
	while (*hex)
	{
		c = ft_tolower(*hex);
		i = 0;
		while (base[i] && base[i] != c)
			i++;
		if (i == 16)
			return (-1);
		res = res * 16 + i;
		hex++;
	}
	return (res);
}

void	*safe_malloc(size_t size, t_data *fdf, int fd)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit_err(fdf, fd, "Memory allocation failed");
	return (ptr);
}

static int	line_is_empty(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	process_line(char *line, t_data *fdf, int fd)
{
	int		cur_width;
	char	*trim;

	trim = ft_strtrim(line, "\n");
	if (!trim)
	{
		free(line);
		exit_err(fdf, fd, "Memory allocation failed");
	}
	cur_width = token_count(trim, ' ');
	free(trim);
	if (fdf->map->width == 0)
		fdf->map->width = cur_width;
	else if (cur_width != fdf->map->width)
	{
		free(line);
		exit_err(fdf, fd, "Inconsistent row width");
	}
	fdf->map->height++;
}

void	get_map_size(char *file, t_data *fdf)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_err(fdf, -1, "Could not open file");
	fdf->map->height = 0;
	fdf->map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!line_is_empty(line))
			process_line(line, fdf, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
