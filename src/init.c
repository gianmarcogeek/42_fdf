/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:15:38 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 15:44:08 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	vars_init(t_vars *vars, char *path)
{
	vars->scale = 75;
	vars->name = path;
	vars->mlx = NULL;
	vars->win = NULL;
	vars->map = NULL;
	vars->def_scale = 0;
	vars->center_x = 0;
	vars->center_y = 0;
	vars->point.xp = 0;
	vars->point.yp = 0;
}

void	mlx_start(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_X, WINDOW_Y, \
				"Fil'e ferru aka FDF | gpuscedd");
	vars->bitmap.img = mlx_new_image(vars->mlx, WINDOW_X, WINDOW_Y);
	vars->bitmap.addr = mlx_get_data_addr(vars->bitmap.img, \
						&(vars->bitmap.bits_per_pixel), \
						&(vars->bitmap.line_lenght), \
						&(vars->bitmap.endian));
}

char	***init_map(char *path, t_vars *vars)
{
	int		fd;
	char	*line;
	char	***map;

	vars->point.x = 0;
	vars->point.y = 0;
	fd = open(path, O_RDWR);
	if (fd < 0 || !ft_strnstr(path, ".fdf", ft_strlen(path)))
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

void	display_istructions(void)
{
	ft_printf("\e[1m\e[42m Change view \e[0m\n");
	ft_printf("\e[1m|-\e[0m translate with arrows\n");
	ft_printf("\e[1m|-\e[0m zoom with [+] / [-]\n");
	ft_printf("\e[1m|-\e[0m reset position [0]\n");
	ft_printf("\e[1m\n");
}

void	display_gui(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, 50, 50, 0xFFFFFF, vars->name);
	mlx_string_put(vars->mlx, vars->win, 50, 30, 0xff2b90, "Fil'e ferru");
	mlx_string_put(vars->mlx, vars->win, 680, 770, 0xFFFFFF, "Isometric view");
}
