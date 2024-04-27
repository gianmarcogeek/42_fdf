/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:11:52 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/27 16:23:21 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	keys_hook(int keysys, t_vars *vars)
{
	if(keysys == 0xff1b) //esc funziona bene
	{
		free_map(&vars->map);
		mlx_destroy_image(vars->mlx, vars->bitmap.img);
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