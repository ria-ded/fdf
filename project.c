/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:59:45 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/05 11:13:19 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	rotate_x(float *y, float *z, float angle_x)
{
	float	prev_y;
	float	prev_z;
	
	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(angle_x) - prev_z * sin(angle_x);
	*z = prev_y * sin(angle_x) + prev_z * cos(angle_x);
}

static void	rotate_y(float *x, float *z, float angle_y)
{
	float	prev_x;
	float	prev_z;
	
	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(angle_y) + prev_z * sin(angle_y);
	*z = - prev_x * sin(angle_y) + prev_z * cos(angle_y);
}

static void	rotate_z(float *x, float *y, float angle_z)
{
	float	prev_x;
	float	prev_y;
	
	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle_z) - prev_y * sin(angle_z);
	*y = prev_x * sin(angle_z) + prev_y * cos(angle_z);
}

void	project_iso_point(t_point *p, t_data *fdf)
{
	float	x;
	float	y;
	float	z;
	float	iso_x;
	float	iso_y;

	x = fdf->zoom * (p->x - fdf->center_x);
	y = fdf->zoom * (p->y - fdf->center_y);
	z = fdf->zoom * (SCALE / 3.0) * p->z;
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
	z = fdf->zoom * (SCALE / 3.0) * p->z;
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


/*
static void	rotate_z(t_point *p)
{
	float	prev_x;
	float	prev_y;
	
	prev_x = p.x;
	prev_y = p.y;
	p.x = prev_x * cos(angle_z) - prev_y * sin(angle_z);
	p.y = prev_x * sin(angle_z) + prev_y * cos(angle_z);
}
*/
