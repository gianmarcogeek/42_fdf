/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 13:36:54 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* TO-DO
	- Provare ad aggiustare proiezione (max fino alle 14)
	- Norminette e Valgrind
	- Capire come "compilare" (./configuration) mlx dal makefile
	- Commentare un po' e iniziare a documentare come esercizio
*/

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc == 2)
	{
		vars_init(&vars, argv[1]);
		mlx_start(&vars);
		vars.map = init_map(argv[1], &vars);
		map_resizing(&vars);
		print_map(&vars);
		mlx_hook(vars.win, 2, 1L << 0, keys_hook, &vars);
		mlx_loop(vars.mlx);
	}
	ft_error("Wrong amount of parameters!\n \
				Try using './fdf <your_map_path>'");
}
