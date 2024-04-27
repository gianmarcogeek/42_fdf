/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:16 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/27 16:22:23 by gpuscedd         ###   ########.fr       */
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

	while(vars->map[y])
	{
		x = 0;
		while(vars->map[y][x]) //per ogni punto della in questa x disegna
		{
			z = ft_atoi(vars->map[y][x]); 
			//come si spostano x e y per creare una proiezione isometrica in funzione di z?
			//devo calcolare le proiezioni anche di x + 1 e di y + 1
			if (vars->map[y][x + 1]) //se c'è un'altro punto alla destra
				bresenham(vars, (x) * vars->scale, (y) * vars->scale, (x + 1) * vars->scale, (y) * vars->scale); //linea orizzontale
			if (vars->map[y + 1]) //se c'è un'altro punto sotto
				bresenham(vars, (x) * vars->scale, (y) * vars->scale, (x) * vars->scale, (y + 1) * vars->scale); //linea verticale
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, vars->center_x, vars->center_y);
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