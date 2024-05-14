/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:56:50 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 13:32:08 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

# define WINDOW_X 800
# define WINDOW_Y 800
# define DEF_LINE_COLOR 0x8cffd0
# define DEF_BACK_COLOR	0x000a25
# define ANGLE 0.6
# define LERP_STEP 0.015

typedef struct s_color
{
	int	trgb;
	int	t;
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		xp;
	int		yp;
	t_color	color;
}				t_point;

//struttura linea (guardare, appuntare e studiare funzionamento bresenhem)
typedef struct s_line
{
	int		xp_curr;
	int		yp_curr;

	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	t_color	color;
}				t_line;

//struttura bitmap, studia un po'
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	***map;
	t_data	bitmap;

	int		scale;
	int		def_scale;
	int		center_x;
	int		center_y;

	t_point	point;
	t_point	p_right;
	t_point	p_down;
	t_line	line;
	char	*name;
}				t_vars;

//init
void	mlx_start(t_vars *vars);
void	vars_init(t_vars *vars, char *path);
char	***init_map(char *path, t_vars *vars);
void	display_gui(t_vars *vars);
void	display_istructions(void);

//utils
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_background(t_vars *vars);
void	ft_error(char *error);
void	bresenham_pixel_put(t_data *data, t_line l);

//bresenham
void	bresenham(t_vars *vars, t_point end);
void	connect_right(t_vars *vars);
void	connect_down(t_vars *vars);

//map_utils
int		ft_count_lines(char *path);
void	scan_points(t_vars *vars);
void	print_map(t_vars *vars);
void	map_resizing(t_vars *vars);
void	free_map(char ****map);

//hooks
int		keys_hook(int keysys, t_vars *vars);
void	translate_view(int keysys, t_vars *vars);
void	scale_view(int keysys, t_vars *vars);

//colors
void	parse_color(t_vars *vars, t_point *p);
int		create_trgb(t_color color);
t_color	lerp_trgb(t_color A, t_color B, float t);
void	split_trgb(t_color *color);

//projection
void	project_xy(t_vars *vars, t_point *p, double angle);

#endif