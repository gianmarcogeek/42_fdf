/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:11:52 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 15:24:34 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	keys_hook(int keysys, t_vars *vars)
{
	if (keysys == 0xff1b)
	{
		free_map(&vars->map);
		mlx_destroy_image(vars->mlx, vars->bitmap.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	translate_view(keysys, vars);
	scale_view(keysys, vars);
	return (0);
}

void	translate_view(int keysys, t_vars *vars)
{
	if (keysys == 0xff51 || keysys == 0x61)
		vars->center_x += 10;
	if (keysys == 0xff53 || keysys == 0x64)
		vars->center_x -= 10;
	if (keysys == 0xff52 || keysys == 0x77)
		vars->center_y += 10;
	if (keysys == 0xff54 || keysys == 0x73)
		vars->center_y -= 10;
	draw_background(vars);
	print_map(vars);
}

void	scale_view(int keysys, t_vars *vars)
{
	if (keysys == 0x2d && vars->scale > 1)
		vars->scale -= 1;
	if ((keysys == 0x2b || keysys == 0x3d) && vars->scale < 500)
		vars->scale += 1;
	if (keysys == 0x30)
	{
		vars->scale = vars->def_scale;
		scan_points(vars);
		vars->center_x = (WINDOW_X / 2) - (vars->point.xp - vars->center_x) / 2;
		vars->center_y = (WINDOW_Y / 2) - (vars->point.yp - vars->center_y) / 2;
	}
	draw_background(vars);
	print_map(vars);
}

int	x_close_event(t_vars *vars)
{
	free_map(&vars->map);
	mlx_destroy_image(vars->mlx, vars->bitmap.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(1);
}
