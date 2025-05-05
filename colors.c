/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:20:52 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/05 10:41:37 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	get_color_channel(int trgb, int shift)
{
	return ((trgb >> shift) & 0xFF);
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

int	get_color(int y, int height)
{
	t_color	color;
	float	ratio;

	ratio = (float)y / (float)height;
	color.t = 0x00;
	color.r = 100 + (int)(100 * ratio);
	color.g = 150 + (int)(50 * (1 - ratio));
	color.b = 255 - (int)(255 * ratio);
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}
