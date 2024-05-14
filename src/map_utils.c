/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:16 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 13:38:04 by gpuscedd         ###   ########.fr       */
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

void	print_map(t_vars *vars)
{
	vars->point.x = 0;
	vars->point.y = 0;
	draw_background(vars);
	while (vars->map[vars->point.y])
	{
		vars->point.x = 0;
		while (vars->map[vars->point.y][vars->point.x])
		{
			vars->point.z = ft_atoi(vars->map[vars->point.y][vars->point.x]);
			parse_color(vars, &vars->point);
			project_xy(vars, &vars->point, ANGLE);
			connect_right(vars);
			connect_down(vars);
			vars->point.x++;
		}
		vars->point.y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, 0, 0);
	display_gui(vars);
}

void	scan_points(t_vars *vars)
{
	vars->point.x = 0;
	vars->point.y = 0;
	while (vars->map[vars->point.y])
	{
		vars->point.x = 0;
		while (vars->map[vars->point.y][vars->point.x])
		{
			vars->point.z = ft_atoi(vars->map[vars->point.y][vars->point.x]);
			project_xy(vars, &vars->point, ANGLE);
			vars->point.x++;
		}
		vars->point.y++;
	}
}

void	map_resizing(t_vars *vars)
{
	scan_points(vars);
	while (vars->point.yp > WINDOW_Y - 100 || vars->point.xp > WINDOW_X - 100)
	{
		vars->scale--;
		scan_points(vars);
	}
	vars->def_scale = vars->scale;
	vars->center_x = (WINDOW_X / 2) - (vars->point.xp / 2);
	vars->center_y = (WINDOW_Y / 2) - (vars->point.yp / 2);
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
