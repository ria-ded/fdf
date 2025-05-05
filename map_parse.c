/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:05:41 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/05 10:41:08 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static t_point	parse_token(t_data *fdf, char *token, int x, int y)
{
	t_point	point;
	char	*comma;

	comma = ft_strchr(token, ',');
	if (comma)
	{
		*comma = '\0';
		point.z = ft_atoi(token);
		point.color.trgb = hex_to_int(comma + 1);
	}
	else
	{
		point.z = ft_atoi(token);
		point.color.trgb = get_color(point.z, fdf->map->height);
	}
	point.x = x;
	point.y = y;
	return (point);
}

static t_point	*parse_x_line(char *line, t_data *fdf, int y, int fd)
{
	t_point	*row;
	char	**tokens;
	int		x;

	row = safe_malloc(sizeof(t_point) * fdf->map->width, fdf, fd);
	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		free(row);
		free(line);
		exit_err(fdf, fd, "Token split failed");
	}
	x = 0;
	while (x < fdf->map->width)
	{
		row[x] = parse_token(fdf, tokens[x], x, y);
		x++;
	}
	free_split(tokens);
	return (row);
}

static void	parse_map(t_data *fdf, int fd)
{
	int		y;
	char	*line;
	char	*trim;

	y = 0;
	while (y < fdf->map->height)
	{
		line = get_next_line(fd);
		if (!line)
			exit_err(fdf, fd, "GNL failed");
		trim = ft_strtrim(line, "\n");
		free(line);
		if (!trim)
			exit_err(fdf, fd, "GNL failed");
		fdf->map->grid[y] = parse_x_line(trim, fdf, y, fd);
		free(trim);
		y++;
	}
}

void	parse_file(t_data *fdf, char *file)
{
	int	fd;

	fdf->map = safe_malloc(sizeof(t_map), fdf, -1);
	get_map_size(file, fdf);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_err(fdf, -1, "Failed to open file");
	fdf->map->grid = safe_malloc(sizeof(t_point *) * fdf->map->height, fdf, fd);
	ft_bzero(fdf->map->grid, fdf->map->height * sizeof(*fdf->map->grid));
	parse_map(fdf, fd);
	close(fd);
}
