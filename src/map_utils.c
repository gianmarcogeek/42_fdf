/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:16 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/28 00:33:26 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int ft_count_lines(char *path)
{
	int fd;
	char *line;
	int n_lines;

	fd = open(path, O_RDWR);
	line = get_next_line(fd);
	n_lines = 1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		n_lines++;
	}
	return(close(fd), n_lines);
}

char ***init_map(char *path, int *map_height, int *map_lenght)
{
	int		x;
	int		y;
	int		fd; 
	char	*line;
	char	***map;

	x = 0;
	y = 0;
	fd = open(path, O_RDWR);
	map = (char ***)malloc((ft_count_lines(path) + 1) * sizeof(char **));
	if(!map)
		return(NULL);
	line = get_next_line(fd);
	while(line)
	{
		map[y++] = ft_split(line, ' ');
		free(line);
		line = get_next_line(fd);
	}
	map[y] = NULL;
	*map_height = y;
	while(map[y - 1][x])
		x++;
	*map_lenght = x;
	return(close(fd), map);
}

void print_map(t_vars *vars)
{
	int x = 0;
	int y = 0;
	int z = 0;

	mlx_string_put(vars->mlx, vars->win, 20, 20, 0xFFFFFF, ft_itoa((int)vars->angle));
	while(vars->map[y])
	{
		x = 0;
		while(vars->map[y][x])
		{
			z = ft_atoi(vars->map[y][x]);
			int x_ISO = ((x - y) * cos(vars->angle) * vars->scale) +(vars->map_lenght/2 * vars->scale) + vars->center_x;
			int y_ISO = ((((x + y) * sin(vars->angle))- z) * vars->scale) + (vars->map_height/4 * vars->scale) + vars->center_y;

			// my_mlx_pixel_put(&vars->bitmap, x_ISO, y_ISO, 0xFF0000);
			
            if (vars->map[y][x + 1]) 
			{
                int x_ISO_right = (((x + 1) - y) * cos(vars->angle) * vars->scale) + (vars->map_lenght/2 * vars->scale) + vars->center_x;
                int y_ISO_right = (((((x + 1) + y) * sin(vars->angle))- ft_atoi(vars->map[y][x + 1])) * vars->scale) + (vars->map_height/4 * vars->scale) + vars->center_y;
                bresenham(vars, x_ISO, y_ISO, x_ISO_right, y_ISO_right);
            }
			
            if (vars->map[y + 1])
			{
                int x_ISO_down = ((x - (y + 1)) * cos(vars->angle) * vars->scale) +(vars->map_lenght/2 * vars->scale) + vars->center_x;
                int y_ISO_down = ((((x + (y + 1)) * sin(vars->angle))- ft_atoi(vars->map[y + 1][x])) * vars->scale) + (vars->map_height/4 * vars->scale) + vars->center_y;
                bresenham(vars, x_ISO, y_ISO, x_ISO_down, y_ISO_down);

				
				// if (vars->map[y + 1][x + 1])
				// {
                // 	int x_ISO_diag = (((x + 1) - (y + 1)) * cos(vars->angle) * vars->scale) +(vars->map_lenght/2 * vars->scale) + vars->center_x;
                // 	int y_ISO_diag = (((((x + 1) + (y + 1)) * sin(vars->angle))- ft_atoi(vars->map[y + 1][x + 1])) * vars->scale) + (vars->map_height/4 * vars->scale) + vars->center_y;
                // 	bresenham(vars, x_ISO, y_ISO, x_ISO_diag, y_ISO_diag);
				// }
			}

			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, 0, 0);
}

void free_map(char ****map)
{
	int x = 0;
	int y = 0;
	while((*map)[y])
		{
			x = 0;
			while((*map)[y][x])
			{
				free((*map)[y][x]);
				x++;
			}
			free((*map)[y]);
			y++;
		}
	free(*map);
}
