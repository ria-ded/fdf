/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 23:36:39 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/03 21:02:31 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	render(t_data *fdf)
{
	clear_win(fdf, GREY);
	project_map(fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}

void	pixel_put(t_data *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = fdf->img.addr + (y * fdf->img.line_len + x * (fdf->img.bpp / 8));
	*(unsigned int *)dst = color;
}
