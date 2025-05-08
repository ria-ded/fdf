/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:20:52 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/07 22:02:07 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	get_color_channel(int trgb, int shift)
{
	return ((trgb >> shift) & 0xFF);
}

int	set_color(int z, t_data *fdf)
{
	t_color	color;
	float	ratio;
	float	range;

	range = fdf->map->z_max - fdf->map->z_min;
	if (range == 0)
		ratio = 0.0f;
	else
		ratio = (float)(z - fdf->map->z_min) / range;
	color.t = 0x00;
	color.r = (int)(200 * ratio);
	color.g = 0;
	color.b = (int)(255 * (1.0f - ratio));
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

float	fraction(int start, int end, int cur)
{
	if (start != end)
		return (((float)cur - (float)start)
			/ ((float)end - (float)start));
	return (0.2f);
}

int	gradient(int x, int y, t_point p0, t_point p1)
{
	t_color	cur;
	float	ratio;

	if (fabsf(p1.y_scr - p0.y_scr) < fabsf(p1.x_scr - p0.x_scr))
		ratio = fraction(p0.x_scr, p1.x_scr, x);
	else
		ratio = fraction(p0.y_scr, p1.y_scr, y);
	p0.color.t = get_color_channel(p0.color.trgb, 24);
	p0.color.r = get_color_channel(p0.color.trgb, 16);
	p0.color.g = get_color_channel(p0.color.trgb, 8);
	p0.color.b = get_color_channel(p0.color.trgb, 0);
	p1.color.t = get_color_channel(p1.color.trgb, 24);
	p1.color.r = get_color_channel(p1.color.trgb, 16);
	p1.color.g = get_color_channel(p1.color.trgb, 8);
	p1.color.b = get_color_channel(p1.color.trgb, 0);
	cur.t = 0x00;
	cur.r = p0.color.r + (p1.color.r - p0.color.r) * ratio;
	cur.g = p0.color.g + (p1.color.g - p0.color.g) * ratio;
	cur.b = p0.color.b + (p1.color.b - p0.color.b) * ratio;
	return (cur.t << 24 | cur.r << 16 | cur.g << 8 | cur.b);
}

/*
float	fraction(int x, int y, t_point p0, t_point p1)
{
	float	dx;
	float	dy;
	float	dist_sq;
	float	ratio;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq == 0)
		return (0.0f);
	ratio = ((x - p0.x) * dx + (y - p0.y) * dy) / dist_sq;
	if (ratio < 0.0f)
		ratio = 0.0f;
	else if (ratio > 1.0f)
		ratio = 1.0f;
	return (ratio);
}

int	gradient(int x, int y, t_point p0, t_point p1)
{
	t_color	cur;
	float	ratio;

	ratio = fraction(x, y, p0, p1);
	p0.color.t = get_color_channel(p0.color.trgb, 24);
	p0.color.r = get_color_channel(p0.color.trgb, 16);
	p0.color.g = get_color_channel(p0.color.trgb, 8);
	p0.color.b = get_color_channel(p0.color.trgb, 0);
	p1.color.t = get_color_channel(p1.color.trgb, 24);
	p1.color.r = get_color_channel(p1.color.trgb, 16);
	p1.color.g = get_color_channel(p1.color.trgb, 8);
	p1.color.b = get_color_channel(p1.color.trgb, 0);
	cur.t = 0x00;
	cur.r = p0.color.r + (p1.color.r - p0.color.r) * ratio;
	cur.g = p0.color.g + (p1.color.g - p0.color.g) * ratio;
	cur.b = p0.color.b + (p1.color.b - p0.color.b) * ratio;
	return (cur.t << 24 | cur.r << 16 | cur.g << 8 | cur.b);
}
*/
