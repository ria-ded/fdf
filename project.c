/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:59:45 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/07 16:01:03 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	project_iso_point(t_point *p, t_data *fdf)
{
	float	x;
	float	y;
	float	z;
	float	iso_x;
	float	iso_y;

	x = fdf->zoom * (p->x - fdf->center_x);
	y = fdf->zoom * (p->y - fdf->center_y);
	z = fdf->zoom * fdf->scale_z * p->z;
	rotate_x(&y, &z, fdf->angle_x);
	rotate_y(&x, &z, fdf->angle_y);
	rotate_z(&x, &y, fdf->angle_z);
	iso_x = (x - y) * cos(ISO_ANGLE);
	iso_y = (x + y) * sin(ISO_ANGLE) - z;
	p->x_scr = iso_x + fdf->offset_x;
	p->y_scr = iso_y + fdf->offset_y;
}

void	project_ortho_point(t_point *p, t_data *fdf)
{
	float	x;
	float	y;
	float	z;

	x = fdf->zoom * (p->x - fdf->center_x);
	y = fdf->zoom * (p->y - fdf->center_y);
	z = fdf->zoom * fdf->scale_z * p->z;
	rotate_x(&y, &z, fdf->angle_x);
	rotate_y(&x, &z, fdf->angle_y);
	rotate_z(&x, &y, fdf->angle_z);
	p->x_scr = x + fdf->offset_x;
	p->y_scr = y + fdf->offset_y - z;
}

void	project_map(t_data *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (fdf->projection == 1)
				project_iso_point(&fdf->map->grid[y][x], fdf);
			else
				project_ortho_point(&fdf->map->grid[y][x], fdf);
			x++;
		}
		y++;
	}
}
