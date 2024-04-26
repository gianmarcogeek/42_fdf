/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:56:50 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/26 16:48:34 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF
#define FDF

# include <fcntl.h>
# include <math.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"


typedef struct	s_data { //capire ogni elemento di questa struct
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	char ***map;
	t_data	image;
	
	int center_x;
	int center_y;
	int scale;
	int window_x;
	int window_y;
	int map_height;
	int map_lenght;
}				t_vars;


void bresenham(t_vars *vars, int A_x, int A_y, int B_x, int B_y);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

int ft_count_lines(char *path);
char ***init_map(char *path, int *map_height, int *map_lenght);
void print_map(t_vars *vars);
void free_map(char ****map);

#endif