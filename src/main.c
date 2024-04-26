/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/26 17:37:33 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* TO-DO

- studia e capisci bresenham
- riordina e norminetta todo
- implementa proiezione isometrica
- gioca con gli hook

*/



void bresenham(t_vars *vars, int A_x, int A_y, int B_x, int B_y)
{
    int dx = abs(B_x - A_x);
    int dy = abs(B_y - A_y);

    int decision;
    if (dx >= dy) {
        decision = 2 * dy - dx;
    } else {
        decision = 2 * dx - dy;
    }

    int x = A_x;
    int y = A_y;
    my_mlx_pixel_put(&vars->image, x, y, 0xFFFFF);

    int s = 1;
    int q = 1;

    if (B_x < A_x)
        q = -1;
    if (B_y < A_y)
        s = -1;

    while (x != B_x || y != B_y)
    {
        if (dx >= dy)
        {
            if (decision >= 0)
            {
                decision += 2 * (dy - dx);
                y += s;
            }
            decision += 2 * dy;
            x += q;
        }
        else
        {
            if (decision >= 0)
            {
                decision += 2 * (dx - dy);
                x += q;
            }
            decision += 2 * dx;
            y += s;
        }
        my_mlx_pixel_put(&vars->image, x, y, 0xFFFFF);
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
	// if(keysys == 0xff51 || keysys == 0x61)
	// {
	// 	vars->center_x -= 10;
	// 	print_map(vars);
	// }
	// if(keysys == 0xff53  || keysys == 0x64)
	// {
	// 	vars->center_x += 10;
	// 	print_map(vars);
	// }

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
	vars.center_x = (vars.window_x / 2) - (vars.map_lenght * vars.scale / 2);
	vars.center_y = (vars.window_y / 2) - (vars.map_height * vars.scale / 2);
	print_map(&vars);
	//bresenham(&vars, 50, 500, 500, 50);
	
	//mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	

	
	mlx_key_hook(vars.win, keys_hook, &vars);
	mlx_loop(vars.mlx);
}
