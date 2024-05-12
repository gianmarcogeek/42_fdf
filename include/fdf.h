/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:56:50 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/13 01:21:56 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
#include <stdio.h>
# include <math.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

# define WINDOW_X 800
# define WINDOW_Y 800
# define DEF_COLOR 0xFFFFFF

typedef struct s_color {
	int trgb;
	int t;
	int r;
	int g;
	int b;
}				t_color;

typedef struct s_point {
	int x;
	int y;
	int z;
	int xp;
	int yp;
	t_color color;
}				t_point;


typedef struct s_line {
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
	t_color color;
} 				t_line;

typedef	struct s_data { //capire ogni elemento di questa struct (è la struttura di un bitmap)
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}				t_data;

typedef struct	s_vars { //da ordinare con sotto strutture tipo map_info / others_vars
	void	*mlx;
	void	*win;
	char ***map;
	t_data	bitmap;
	
	int map_height;
	int map_lenght;
	
	int scale;
	int center_x;
	int center_y;

	double angle;

	t_point point;
	t_point p_right;
	t_point p_down;
	int def_scale;

	t_line line;
	char *name;
	double x_angle;
	int *max_xp;
	int *max_yp;
	
}				t_vars;

//draw_utils
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_background(t_vars *vars);

//bresenham
void	bresenham(t_vars *vars, t_point end);
void	connect_right(t_vars *vars);
void	connect_down(t_vars *vars);

//map_utils
int ft_count_lines(char *path);
char ***init_map(char *path, t_vars *vars);
void	scan_points(t_vars *vars);
void print_map(t_vars *vars);
void	map_resizing(t_vars *vars);
void free_map(char ****map);
//hooks
int	keys_hook(int keysys, t_vars *vars);
int x_close_event(t_vars *vars);

//colors
t_color calculate_color(t_color A, t_color B, float t);
int	create_trgb(t_color color);
void split_trgb(t_color *color);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

//error
void display_error(char *error);

#endif