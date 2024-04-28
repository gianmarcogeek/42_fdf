/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:16 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/28 12:17:45 by gpuscedd         ###   ########.fr       */
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
	int xp;
	int yp;
	while(vars->map[y])
	{
		x = 0;
		while(vars->map[y][x])
		{
			z = ft_atoi(vars->map[y][x]);
			xp = (x - y) * cos(vars->angle) * vars->scale + vars->center_x;
			yp = ((x + y) * sin(vars->angle) - z) * vars->scale + vars->center_y;
			
			connect_right(vars, x, y, xp, yp, vars->center_x, vars->center_y);
			connect_down(vars, x, y, xp, yp, vars->center_x, vars->center_y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, 0, 0);
	mlx_string_put(vars->mlx, vars->win, 100, 50, 0xFFFFFF, ft_strjoin("Zoom x", ft_itoa(vars->scale)));
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
