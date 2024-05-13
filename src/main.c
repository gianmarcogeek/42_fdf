/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/13 21:40:20 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* TO-DO
	- Norminette e Valgrind
	- Capire come "compilare" (./configuration) mlx dal makefile
*/

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
		vars.point.color.trgb = DEF_LINE_COLOR;

		mlx_start(&vars);
		vars.map = init_map(argv[1], &vars);
		map_resizing(&vars);
		print_map(&vars);
		mlx_hook(vars.win, 2, 1L<<0, keys_hook, &vars);
		mlx_loop(vars.mlx);
	}
	ft_error("Wrong amount of parameters!\nTry using './fdf <your_map_path>'");
}
