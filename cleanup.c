/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:16:03 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/08 19:07:07 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	y = 0;
	if (map->grid)
	{
		while (y < map->height)
		{
			free(map->grid[y]);
			y++;
		}
		free(map->grid);
	}
	free(map);
}

void	free_fdf(t_data *fdf)
{
	if (!fdf)
		return ;
	if (fdf->mlx && fdf->img.img)
	{
		mlx_destroy_image(fdf->mlx, fdf->img.img);
		fdf->img.img = NULL;
	}
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->map)
		free_map(fdf->map);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf);
}

void	exit_err(t_data *fdf, int fd, char *msg)
{
	if (msg)
		perror(msg);
	if (fd >= 0)
		close (fd);
	if (fdf)
		free_fdf(fdf);
	exit(EXIT_FAILURE);
}

void	clear_win(t_data *fdf, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_put(fdf, x, y, color);
			x++;
		}
		y++;
	}
}
