/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/23 01:12:26 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_and_free(int keysys, t_vars *vars)
{
	if(keysys == 0xff1b)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	return (0);
}

int	main()
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "Let's go!");
	img.img = vars.img = mlx_new_image(vars.mlx, 900, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);



	
	int fd = open("test.txt", O_RDWR);
	char ***map = (char ***)malloc(sizeof(char ***));
	char *prova = get_next_line(fd);
	int y = 0;
	int x = 0;
	int x1 = 0;
	int y1 = 0;
	int xISO = 0;
	int yISO = 0;
	int z_value = 0;
	map[y++] = ft_split(prova, ' ');
	while(prova)
	{
		prova = get_next_line(fd); //ottengo una riga
		map[y] = ft_split(prova, ' ');
		y++;	
	}
	map[y] = NULL;
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			z_value = ft_atoi(map[y][x]);
			x1 = x * 10;
			y1 = y * 10;
			xISO = (x1 - y1) * cos(0.5);
			yISO = -z_value + (x1 + y1) * sin(0.5);

			my_mlx_pixel_put(&img, (xISO + 40)*8, (yISO + 40)*8, 0xFFFFFF);		
			x++;
		}
		y++;
	}


 
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 100, 100);
	
	mlx_key_hook(vars.win, close_and_free, &vars);
	mlx_loop(vars.mlx);
}
