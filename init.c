/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:01:11 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/08 16:33:36 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_data	*fdf_init(char *file)
{
	t_data	*fdf;

	fdf = malloc(sizeof(t_data));
	if (!fdf)
		return (NULL);
	ft_memset(fdf, 0, sizeof(t_data));
	fdf->has_exited = 0;
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (free(fdf), NULL);
	parse_file(fdf, file);
	fdf->projection = 1;
	set_default(fdf);
	fdf->zoom = fminf((float)WIDTH / (float)fdf->map->width,
			(float)HEIGHT / (float)fdf->map->height) * SCALE;
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, file);
	fdf->img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.line_len, &fdf->img.endian);
	return (fdf);
}

void	set_default(t_data *fdf)
{
	float	range;

	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 2;
	fdf->angle_x = 0.0f;
	fdf->angle_y = 0.0f;
	fdf->angle_z = 0.0f;
	fdf->center_x = (fdf->map->width - 1) / 2.0;
	fdf->center_y = (fdf->map->height - 1) / 2.0;
	fdf->zoom = fminf((float)WIDTH / (float)fdf->map->width,
			(float)HEIGHT / (float)fdf->map->height) * SCALE;
	fdf->scale_z = 1.0;
	range = fdf->map->z_max - fdf->map->z_min;
	if (range > 0)
		fdf->scale_z = (float)fdf->map->height / (float)range * 0.5;
}
