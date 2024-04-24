/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/25 01:33:00 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_and_free(int keysys, t_vars *vars)
{
			int x = 0;
			int y = 0;
			while(vars->map[y])
			{
			x = 0;
			while(vars->map[y][x])
			{
				free(vars->map[y][x]);
				x++;
			}
			free(vars->map[y]);
			y++;
			}
			free(vars->map);
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);

	return (0);
}

int ft_count_lines(char *path)
{
	int fd;
	char *line;
	int n_lines;
	
	n_lines = 0;
	line = NULL;
	n_lines++;
	fd = open(path, O_RDWR);
	line = get_next_line(fd);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		n_lines++;
	}
	close(fd);
	return(n_lines);
}


char ***init_map(char *path)
{
	int y;
	char *line;
	char ***map;
	int fd; 
	
	
	y = 0;
	map = (char ***)malloc((ft_count_lines(path) + 1) * sizeof(char **));
	fd = open(path, O_RDWR);
	line = get_next_line(fd);
	if(!map)
		return(NULL);
	while(line)
	{
		map[y] = ft_split(line, ' ');
		free(line);
		line = get_next_line(fd);
		y++;
	}
	map[y] = NULL;
	close(fd);
	return(map);
}

int	main()
{
	t_vars	vars;
	int x = 0;
	int y = 0;
	int z = 0;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "Fil'e ferru BETA");
	vars.img.img = mlx_new_image(vars.mlx, 900, 900);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_lenght, &vars.img.endian);

	vars.map = init_map("test.txt");
	
	while(vars.map[y])
	{
		x = 0;
		while(vars.map[y][x])
		{
			z = ft_atoi(vars.map[y][x]);
			my_mlx_pixel_put(&vars.img, x*15, y*15, 0xFF00FF);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 100, 100);
	
	mlx_key_hook(vars.win, close_and_free, &vars);
	mlx_loop(vars.mlx);
}
