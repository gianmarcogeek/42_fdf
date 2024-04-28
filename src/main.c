/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/28 13:06:19 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* TO-DO

- studia, capisci e spezza in funzioni norminettate algoritmo bresenhem
- capisci e implementa il controllo colori e mappa con colori

EXTRA:
- implementa resizing basato sul valore massimo di xp / yp ... se sforano le 
	dimensioni della win di 100 diminuisci la scala per farle entrare;
- aggiungi controllo e display errori vari
- aggiungi un menù con istruzioni per l'uso e hooks
	- aggiungi vista di lato e dall'alto (S - U)
	- traslazione con frecciette
	- modifica scala con rotellina mouse
	- modifica prospettiva entro un range tipo 0 - 0.8 con il tasto P
	- implementa funzionamento a tasto premuto e non solo al rilascio
- capisci come implementare rotazione sull'asse z
- display delle info a schermo / zoom e angolo
- display sul terminale delle info mappa / kb della mappa, dimensioni mappa



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
		
		if((vars.map_height * vars.scale) > WINDOW_Y - 300)
		{
			while((vars.map_height * vars.scale) > WINDOW_Y - 300)
				vars.scale--;
		} //da cambiare con un resizing che si basa sulla yp / xp massima

		vars.center_x = (WINDOW_X / 2) - ((vars.map_lenght * vars.scale) / 2); //anche il centro deve essere basato su la xp / yp massima
		vars.center_y = (WINDOW_Y / 2) - ((vars.map_height * vars.scale) / 3);
		print_map(&vars);

		mlx_key_hook(vars.win, keys_hook, &vars);
		mlx_hook(vars.win, 17, 0, &x_close_event, &vars);
		mlx_loop(vars.mlx);
	}
	ft_printf("ARG ERROR");
	exit(1);
}
