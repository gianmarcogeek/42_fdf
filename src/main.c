/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/11 18:16:13 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* TO-DO
	- Bresenham con color interpolation tra A e B
		* Capire come fare la sfumatura (scomponi colore iniziale e finale in r-g-b, calcola i tre delta e in base al segno calcola il passo (+/-))
	- Gestione errori
		* mappa inesistente (controllo sul open)
		* file mappa che non rispetta le richieste ad esempio
			(minimo due punti)
			(lettere prima della virgola)
			(lettere dopo la f dopo la virgola)
		* 
*/

static void display_istructions(void)
{
	ft_printf("\e[1m\e[42m Change view \e[0m\n");
	ft_printf("\e[1m|-\e[0m translate with arrows\n");
	ft_printf("\e[1m|-\e[0m zoom with [+] / [-]\n");
	ft_printf("\e[1m|-\e[0m reset position [0]\n");
	ft_printf("\e[1m\n");
}

void display_error(char *error)
{
	ft_printf("Error! %s", error);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	if (argc == 2)
	{
		//queste devono essere macro
		vars.scale = 75;
		vars.angle = 0.6;
		vars.angle = 0.5;
		vars.name = argv[1] + 5;
		vars.point.color.trgb = DEF_COLOR;
		
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, WINDOW_X, WINDOW_Y, "Fil'e ferru aka FDF | gpuscedd");

		vars.bitmap.img = mlx_new_image(vars.mlx, WINDOW_X, WINDOW_Y);
		vars.bitmap.addr = mlx_get_data_addr(vars.bitmap.img, \
		&vars.bitmap.bits_per_pixel, &vars.bitmap.line_lenght, \
		&vars.bitmap.endian);
		
		ft_printf("Wait! Loading the map...\n\n");
		
		vars.map = init_map(argv[1], &vars);
		
		display_istructions();
		map_resizing(&vars); //da cambiare con un resizing che si basa sulla yp / xp massima fa cacare!!
		
		vars.center_x = (WINDOW_X / 2) - (vars.point.xp / 2) ; //anche il centro deve essere basato su la xp / yp massima
		vars.center_y = (WINDOW_Y / 2) - (vars.point.yp / 2);
		
		draw_background(&vars);
		print_map(&vars);

		mlx_hook(vars.win, 17, 0, &x_close_event, &vars);
		mlx_hook(vars.win, 2, 1L<<0, keys_hook, &vars);
		mlx_loop(vars.mlx);
	}
	ft_printf("ARG ERROR");
	exit(1);
}
