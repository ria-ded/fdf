/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:40:08 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/05 11:15:58 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int	exit_program(t_data *fdf)
{
	if (fdf->has_exited)
		return (0);
	fdf->has_exited = 1;
	free_fdf(fdf);
	exit (EXIT_SUCCESS);
}

static int	mouse_move(int x, int y, t_data *fdf)
{
	fdf->mouse_x = x;
	fdf->mouse_y = y;
	return (0);
}

static int	mouse_zoom(int button, int x, int y, t_data *fdf)
{
	(void)x;
	(void)y;

	if (button == MOUSE_SCROLL_UP)
	{
		fdf->zoom += 1;
		fdf->offset_x -= (fdf->mouse_x - fdf->offset_x) / 10;
		fdf->offset_y -= (fdf->mouse_y - fdf->offset_y) / 10;
	}
	else if (button == MOUSE_SCROLL_DOWN && fdf->zoom > 1)
	{
		if (fdf->zoom > 1)
			fdf->zoom -= 1;
		fdf->offset_x += (fdf->mouse_x - fdf->offset_x) / 10;
		fdf->offset_y += (fdf->mouse_y - fdf->offset_y) / 10;
	}
	render(fdf);
	return (0);
}

static void	key_zoom(int keycode, t_data *fdf)
{
	if (keycode == KEY_PLUS)
		fdf->zoom += 1;
	if (keycode == KEY_MINUS)
		fdf->zoom -= 1;
}

static void	key_move(int keycode, t_data *fdf)
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

static void	key_rotate(int keycode, t_data *fdf)
{
	if (keycode == KEY_X)
		fdf->angle_x += 10 * (M_PI / 180.0f);
	if (keycode == KEY_Y)
		fdf->angle_y += 10 * (M_PI / 180.0f);
	if (keycode == KEY_Z)
		fdf->angle_z += 10 * (M_PI / 180.0f);
}

static void	key_reset(t_data *fdf)
{
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 2;
	fdf->angle_x = 0.0f;
	fdf->angle_y = 0.0f;
	fdf->angle_z = 0.0f;
	fdf->zoom = fminf((float)WIDTH / (float)fdf->map->width,
			(float)HEIGHT / (float)fdf->map->height) * SCALE;
}

static void	key_centralise(t_data *fdf)
{
	fdf->center_x = (fdf->map->width - 1) / 2.0;
	fdf->center_y = (fdf->map->height - 1) / 2.0;
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 2;
}

static void	key_project(int keycode, t_data *fdf)
{
	if (keycode == ISO)
		fdf->projection = 1;
	if (keycode == ORTHO)
		fdf->projection = 2;
}

static int	handle_key(int keycode, t_data *fdf)
{
	if (keycode == KEY_ESC)
		exit_program(fdf);
	if (keycode == KEY_X || keycode == KEY_Y || keycode == KEY_Z)
		key_rotate(keycode, fdf);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		key_zoom(keycode, fdf);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		key_move(keycode, fdf);
	if (keycode == KEY_R)
		key_reset(fdf);
	if (keycode == ISO || keycode == ORTHO)
		key_project(keycode, fdf);
	if (keycode == KEY_C)
		key_centralise(fdf);
	render(fdf);
	return (0);
}

void	handle_events(t_data *fdf)
{
	mlx_hook(fdf->win, 2, 0, handle_key, fdf);
	mlx_hook(fdf->win, 6, 1L << 6, mouse_move, fdf);
	mlx_mouse_hook(fdf->win, mouse_zoom, fdf);
	mlx_hook(fdf->win, 17, 0, exit_program, fdf);
	mlx_loop(fdf->mlx);
}

/* SIMPLE VERSION

static int	handle_key(int keycode, t_data *fdf)
{
	if (keycode == KEY_ESC)
		exit_program(fdf);
	if (keycode == KEY_PLUS)
		fdf->zoom += 1;
	if (keycode == KEY_MINUS)
		fdf->zoom -= 1;
	if (keycode == KEY_LEFT)
		fdf->offset_x -= 10;
	if (keycode == KEY_RIGHT)
		fdf->offset_x += 10;
	if (keycode == KEY_UP)
		fdf->offset_y -= 10;
	if (keycode == KEY_DOWN)
		fdf->offset_y += 10;
	if (keycode == KEY_X)
		fdf->angle_x += 10 * (M_PI / 180.0f);
	if (keycode == KEY_Y)
		fdf->angle_y += 10 * (M_PI / 180.0f);
	render(fdf);
	return (0);
}

*/
