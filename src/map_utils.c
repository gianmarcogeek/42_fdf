/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:07:16 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/25 19:08:33 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

char ***init_map(char *path, int *map_height, int *map_lenght)
{
	int y;
	int x;
	char *line;
	char ***map;
	int fd; 

	x = 0;
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
	*map_height = y;
	while(map[y - 1][x])
		x++;
	*map_lenght = x;
	close(fd);
	return(map);
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