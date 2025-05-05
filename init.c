/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:01:11 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/05 11:07:37 by mdziadko         ###   ########.fr       */
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
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 2;
	fdf->angle_x = 0.0f;
	fdf->angle_y = 0.0f;
	fdf->angle_z = 0.0f;
	fdf->projection = 1;
	parse_file(fdf, file);
	fdf->center_x = (fdf->map->width - 1) / 2.0;
	fdf->center_y = (fdf->map->height - 1) / 2.0;
	fdf->zoom = fminf((float)WIDTH / (float)fdf->map->width,
			(float)HEIGHT / (float)fdf->map->height) * SCALE;
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, file);
	fdf->img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.line_len, &fdf->img.endian);
	return (fdf);
}
