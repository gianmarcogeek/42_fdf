/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:15:38 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/13 21:23:58 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	mlx_start(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_X, WINDOW_Y, "Fil'e ferru aka FDF | gpuscedd");

	vars->bitmap.img = mlx_new_image(vars->mlx, WINDOW_X, WINDOW_Y);
	vars->bitmap.addr = mlx_get_data_addr(vars->bitmap.img,
						&(vars->bitmap.bits_per_pixel), &(vars->bitmap.line_lenght),
						&(vars->bitmap.endian));
}