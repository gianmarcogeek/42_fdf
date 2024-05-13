/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:16 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/13 21:39:48 by gpuscedd         ###   ########.fr       */
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

char	***init_map(char *path, t_vars *vars)
{
	int		fd;
	char	*line;
	char	***map;

	vars->point.x = 0;
	vars->point.y = 0;
	fd = open(path, O_RDWR);
	if(fd < 0 || !ft_strnstr(path, ".fdf", ft_strlen(path)))
		ft_error("Are you sure this is a .fdf map and you have all rights?");
	ft_printf("Wait! Loading the map...\n\n");
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
	while (map[vars->point.y - 1][vars->point.x])
		vars->point.x++;
	display_istructions();
	return (close(fd), map);
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
			if((ft_strchr(vars->map[vars->point.y][vars->point.x], ',')) != NULL)
				vars->point.color.trgb = ft_atoi_base((ft_strchr(vars->map[vars->point.y][vars->point.x], ',') + 3), 16);
			else
				vars->point.color.trgb = DEF_LINE_COLOR;
			vars->point.xp = (vars->point.x - vars->point.y) * cos(vars->angle) * vars->scale + vars->center_x;
			vars->point.yp = ((vars->point.x + vars->point.y) * sin(vars->angle) - vars->point.z) * vars->scale + vars->center_y;
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
			vars->point.xp = (vars->point.x - vars->point.y) * cos(vars->angle) * vars->scale + vars->center_x;
			vars->point.yp = ((vars->point.x + vars->point.y) * sin(vars->angle) - vars->point.z) * vars->scale + vars->center_y;
			vars->point.x++;
		}
		vars->point.y++;
	}
}

void	map_resizing(t_vars *vars)
{
	scan_points(vars);
	if (((vars->point.yp) > WINDOW_Y) || (vars->point.xp > WINDOW_X))
	{
		while ((vars->point.yp > WINDOW_Y - 150) || vars->point.xp > WINDOW_X - 150)
		{
			vars->scale--;
			scan_points(vars);
		}
	}
	vars->center_x = (WINDOW_X / 2) - (vars->point.xp / 2) ;
	vars->center_y = (WINDOW_Y / 2) - (vars->point.yp / 2);
	vars->def_scale = vars->scale;
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
