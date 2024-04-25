/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/25 19:45:58 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* TO-DO

- implementa bresenham in un programma esterno
- riordina e norminetta todo
- implementa bresenham con logica per collegare tutti i punti
- implemente proiezione isometrica
- gioca con gli hook

*/



void print_map(t_vars *vars)
{
	int x = 0;
	int y = 0;
	int z = 0;
	while(vars->map[y])
	{
		x = 0;
		while(vars->map[y][x])
		{
			z = ft_atoi(vars->map[y][x]);
			my_mlx_pixel_put(&vars->image, x * vars->scale, y * vars->scale, 0xFF00FF);
			vars->center_x = (vars->window_x / 2) - (vars->map_lenght * vars->scale / 2);
			vars->center_y = (vars->window_y / 2) - (vars->map_height * vars->scale / 2);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, vars->center_x, vars->center_y);
			x++;
		}
		y++;
	}
}

int	keys_hook(int keysys, t_vars *vars)
{
	if(keysys == 0xff1b)
	{
		free_map(&vars->map);
		mlx_destroy_image(vars->mlx, vars->image.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	if(keysys == 0xff51)
	{
		vars->center_x--;
		print_map(vars);
	}

	return (0);
}

int	main()
{
	t_vars	vars;

	vars.window_x = 1280;
	vars.window_y = 720;
	vars.scale = 50;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.window_x, vars.window_y, "Fil'e ferru BETA");
	vars.image.img = mlx_new_image(vars.mlx, vars.window_x, vars.window_y);
	vars.image.addr = mlx_get_data_addr(vars.image.img, &vars.image.bits_per_pixel, &vars.image.line_lenght, &vars.image.endian);

	vars.map_height = 0;
	vars.map_lenght = 0;
	vars.map = init_map("test.txt", &vars.map_height, &vars.map_lenght);
	print_map(&vars);

	
	mlx_key_hook(vars.win, keys_hook, &vars);
	mlx_loop(vars.mlx);
}
