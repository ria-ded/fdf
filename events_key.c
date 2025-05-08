/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:38:27 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/06 15:39:06 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	key_zoom(int keycode, t_data *fdf)
{
	if (keycode == KEY_PLUS)
		fdf->zoom *= 1.1;
	if (keycode == KEY_MINUS)
		fdf->zoom *= 0.9;
}

void	key_move(int keycode, t_data *fdf)
{
	if (keycode == KEY_LEFT)
		fdf->offset_x -= 10;
	if (keycode == KEY_RIGHT)
		fdf->offset_x += 10;
	if (keycode == KEY_UP)
		fdf->offset_y -= 10;
	if (keycode == KEY_DOWN)
		fdf->offset_y += 10;
}

void	key_rotate(int keycode, t_data *fdf)
{
	if (keycode == KEY_X)
		fdf->angle_x += 10 * (M_PI / 180.0f);
	if (keycode == KEY_Y)
		fdf->angle_y += 10 * (M_PI / 180.0f);
	if (keycode == KEY_Z)
		fdf->angle_z += 10 * (M_PI / 180.0f);
}

void	key_centralise(t_data *fdf)
{
	fdf->center_x = (fdf->map->width - 1) / 2.0;
	fdf->center_y = (fdf->map->height - 1) / 2.0;
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 2;
}

void	key_project(int keycode, t_data *fdf)
{
	if (keycode == ISO)
		fdf->projection = 1;
	if (keycode == ORTHO)
		fdf->projection = 2;
}
