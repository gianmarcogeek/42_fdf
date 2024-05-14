/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:49:57 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 15:36:35 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc == 2)
	{
		vars_init(&vars, argv[1]);
		vars.map = init_map(argv[1], &vars);
		mlx_start(&vars);
		map_resizing(&vars);
		print_map(&vars);
		mlx_hook(vars.win, 2, 1L << 0, keys_hook, &vars);
		mlx_hook(vars.win, 17, 1L << 0, x_close_event, &vars);
		mlx_loop(vars.mlx);
	}
	ft_error("Wrong amount of parameters!\n \
 Try using './fdf <your_map_path>'");
}
