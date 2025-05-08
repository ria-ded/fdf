/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:45:39 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/05 17:49:37 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	rotate_x(float *y, float *z, float angle_x)
{
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(angle_x) - prev_z * sin(angle_x);
	*z = prev_y * sin(angle_x) + prev_z * cos(angle_x);
}

void	rotate_y(float *x, float *z, float angle_y)
{
	float	prev_x;
	float	prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(angle_y) + prev_z * sin(angle_y);
	*z = -prev_x * sin(angle_y) + prev_z * cos(angle_y);
}

void	rotate_z(float *x, float *y, float angle_z)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle_z) - prev_y * sin(angle_z);
	*y = prev_x * sin(angle_z) + prev_y * cos(angle_z);
}
