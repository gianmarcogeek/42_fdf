/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:16 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/06 23:04:49 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_count_lines(char *path)
{
	int		fd;
	char	*line;
	int		n_lines;

	fd = open(path, O_RDWR);
	line = get_next_line(fd);
	n_lines = 1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		n_lines++;
	}
	return (close(fd), n_lines);
}

char	***init_map(char *path, int *map_height, int *map_lenght, t_vars *vars)
{
	int		fd;
	char	*line;
	char	***map;

	vars->point.x = 0;
	vars->point.y = 0;
	fd = open(path, O_RDWR);
	map = (char ***)malloc((ft_count_lines(path) + 1) * sizeof(char **));
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		map[vars->point.y++] = ft_split(line, ' ');
		free(line);
		line = get_next_line(fd);
	}
	map[vars->point.y] = NULL;
	*map_height = vars->point.y;
	while (map[vars->point.y - 1][vars->point.x])
		vars->point.x++;
	*map_lenght = vars->point.x;
	return (close(fd), map);
}

void	print_map(t_vars *vars)
{
	vars->point.x = 0;
	vars->point.y = 0;
	while (vars->map[vars->point.y])
	{
		vars->point.x = 0;
		while (vars->map[vars->point.y][vars->point.x])
		{
			vars->point.z = ft_atoi(vars->map[vars->point.y][vars->point.x]);
			vars->point.xp = (vars->point.x - vars->point.y) * cos(vars->angle) * vars->scale + vars->center_x;
			vars->point.yp = ((vars->point.x + vars->point.y) * sin(vars->angle) - vars->point.z) * vars->scale + vars->center_y;
			connect_right(vars);
			connect_down(vars);
			vars->point.x++;
		}
		vars->point.y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, 0, 0);
	mlx_string_put(vars->mlx, vars->win, 100, 50, 0xFFFFFF, ft_strjoin("Zoom x", ft_itoa(vars->scale)));
}

void	free_map(char ****map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while ((*map)[y])
	{
		x = 0;
		while ((*map)[y][x])
		{
			free((*map)[y][x]);
			x++;
		}
		free((*map)[y]);
		y++;
	}
	free(*map);
}
