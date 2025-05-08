/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:36:36 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/07 22:03:57 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	draw_line_h(t_data *fdf, t_point p0, t_point p1, int dir)
{
	int	dx;
	int	dy;
	int	y;
	int	x;
	int	err;

	dx = fabsf(p1.x_scr - p0.x_scr);
	dy = fabsf(p1.y_scr - p0.y_scr);
	if (p1.y_scr < p0.y_scr)
		dir = -1;
	y = p0.y_scr;
	x = p0.x_scr;
	err = 2 * dy - dx;
	while (x <= p1.x_scr)
	{
		pixel_put(fdf, x, y, gradient(x, y, p0, p1));
		if (err >= 0)
		{
			y += dir;
			err -= 2 * dx;
		}
		err += 2 * dy;
		x++;
	}
}

static void	draw_line_v(t_data *fdf, t_point p0, t_point p1, int dir)
{
	int	dx;
	int	dy;
	int	y;
	int	x;
	int	err;

	dx = fabsf(p1.x_scr - p0.x_scr);
	dy = fabsf(p1.y_scr - p0.y_scr);
	if (p1.x_scr < p0.x_scr)
		dir = -1;
	y = p0.y_scr;
	x = p0.x_scr;
	err = 2 * dx - dy;
	while (y <= p1.y_scr)
	{
		pixel_put(fdf, x, y, gradient(x, y, p0, p1));
		if (err >= 0)
		{
			x += dir;
			err -= 2 * dy;
		}
		err += 2 * dx;
		y++;
	}
}

void	draw_line(t_data *fdf, t_point p0, t_point p1)
{
	int	dir;

	dir = 1;
	if (p0.color.trgb == -1)
		p0.color.trgb = set_color(p0.z, fdf);
	if (p1.color.trgb == -1)
		p1.color.trgb = set_color(p1.z, fdf);
	if (fabsf(p1.y_scr - p0.y_scr) < fabsf(p1.x_scr - p0.x_scr))
	{
		if (p0.x_scr > p1.x_scr)
			draw_line_h(fdf, p1, p0, dir);
		else
			draw_line_h(fdf, p0, p1, dir);
	}
	else
	{
		if (p0.y_scr > p1.y_scr)
			draw_line_v(fdf, p1, p0, dir);
		else
			draw_line_v(fdf, p0, p1, dir);
	}
}

void	draw_map(t_data *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x + 1 < fdf->map->width)
				draw_line(fdf,
					fdf->map->grid[y][x],
					fdf->map->grid[y][x + 1]);
			if (y + 1 < fdf->map->height)
				draw_line(fdf,
					fdf->map->grid[y][x],
					fdf->map->grid[y + 1][x]);
			x++;
		}
		y++;
	}
}

/*
void	draw_line(t_point p0, t_point p1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;

	dx = abs(p1.x - p0.x);
	sx = 1;
	if (p1.x < p0.x)
		sx = -1;
	dy = -abs(p1.y - p0.y);
	sy = 1;
	if (p1.y < p0.y)
		sy = -1;
	error = dy + dx;
	if (dy > dx)
	{
		while (p1.y < p0.y)
	}
	else
	{
		
	}
}

*/
