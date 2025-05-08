/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:30:45 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/07 21:31:48 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define WIDTH 1400
# define HEIGHT 920
# define SCALE 0.7f
# define ISO_ANGLE 0.523599

# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define GREEN 0x0089F336
# define GREY 0x000a0a0f

# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_PLUS 61
#  define KEY_MINUS 45
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_UP 65362
#  define KEY_X 45
#  define KEY_Y 21
#  define KEY_Z 122
#  define KEY_R 27
#  define KEY_C 99
#  define ISO 49
#  define ORTHO 50
# else
#  define KEY_ESC 53
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_X 7
#  define KEY_Y 16
#  define KEY_Z 6
#  define KEY_R 15
#  define KEY_C 8
#  define ISO 18
#  define ORTHO 19
# endif

typedef struct s_color
{
	int	trgb;
	int	t;
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	t_color	color;
	float	x_scr;
	float	y_scr;
}		t_point;

typedef struct s_map
{
	t_point	**grid;
	int		width;
	int		height;
	float	z_min;
	float	z_max;
}			t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	img;
	int		offset_x;
	int		offset_y;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	int		mouse_x;
	int		mouse_y;
	int		center_x;
	int		center_y;
	float	zoom;
	float	scale_z;
	int		projection;
	int		has_exited;
}			t_data;

// INIT
t_data	*fdf_init(char *file);
void	set_default(t_data *fdf);

// PARSING
void	parse_file(t_data *fdf, char *file);

// PARSE UTILS
int		hex_to_int(char *hex);
void	get_map_size(char *file, t_data *fdf);
void	*safe_malloc(size_t size, t_data *fdf, int fd);

// PROJECTION
void	project_iso_point(t_point *p, t_data *fdf);
void	project_ortho_point(t_point *p, t_data *fdf);
void	project_map(t_data *fdf);

// ROTATION
void	rotate_x(float *y, float *z, float angle_x);
void	rotate_y(float *x, float *z, float angle_y);
void	rotate_z(float *x, float *y, float angle_z);

// DRAWING
void	draw_line(t_data *fdf, t_point p0, t_point p1);
void	draw_map(t_data *fdf);

// COLORS
int		get_color_channel(int trgb, int shift);
// float	fraction(int x, int y, t_point p0, t_point p1);
float	fraction(int start, int end, int cur);
int		gradient(int x, int y, t_point p0, t_point p1);
int		set_color(int y, t_data *fdf);

// RENDER
void	pixel_put(t_data *fdf, int x, int y, int color);
void	render(t_data *fdf);

// EVENTS
void	handle_events(t_data *fdf);
int		handle_key(int keycode, t_data *fdf);
int		exit_program(t_data *fdf);
int		mouse_move(int x, int y, t_data *fdf);
int		mouse_zoom(int button, int x, int y, t_data *fdf);

// EVENTS KEY
void	key_zoom(int keycode, t_data *fdf);
void	key_move(int keycode, t_data *fdf);
void	key_rotate(int keycode, t_data *fdf);
void	key_centralise(t_data *fdf);
void	key_project(int keycode, t_data *fdf);

// CLEANUP
void	exit_err(t_data *fdf, int fd, char *msg);
void	free_map(t_map *map);
void	free_fdf(t_data *fdf);
void	clear_win(t_data *fdf, int color);

#endif