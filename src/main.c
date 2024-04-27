/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/28 00:11:56 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* TO-DO

- studia e capisci bresenham
- spezzetta bresenham in varie funzioni norminettate
- riordina e norminetta todo
- capisci come non far andare in segfault se la mappa sfora la window

- implementa proiezione isometrica
- gioca con gli hook
- aggiungi menu instruzioni e altri extra

*/

int	main(int argc, char *argv[])
{
	t_vars	vars;
	if (argc == 2)
	{
		vars.scale = 80;
		vars.angle = 0.6;

		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, WINDOW_X, WINDOW_Y, "Fil'e ferru");

		vars.bitmap.img = mlx_new_image(vars.mlx, WINDOW_X, WINDOW_Y);
		vars.bitmap.addr = mlx_get_data_addr(vars.bitmap.img, \
		&vars.bitmap.bits_per_pixel, &vars.bitmap.line_lenght, \
		&vars.bitmap.endian);

		vars.map = init_map(argv[1], &vars.map_height, &vars.map_lenght);

		vars.center_x = (WINDOW_X / 2) - ((vars.map_lenght * vars.scale) / 2);
		vars.center_y = (WINDOW_Y / 2) - ((vars.map_height * vars.scale) / 2);
		print_map(&vars);

		mlx_key_hook(vars.win, keys_hook, &vars);
		mlx_hook(vars.win, 17, 0, &x_close_event, &vars);
		mlx_loop(vars.mlx);
	}
	ft_printf("ARG ERROR");
	exit(1);
}
