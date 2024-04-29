/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:01:03 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/29 11:15:00 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if ((x >= 0 && x < WINDOW_X) && (y >= 0 && y < WINDOW_Y))
	{
		offset = (y * data->line_lenght + x * (data->bits_per_pixel / 8));
		dst = data->addr + offset;
		*(unsigned int *) dst = color;
	}
}

void	draw_background(t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WINDOW_Y)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			my_mlx_pixel_put(&vars->bitmap, x, y, 0x000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, 0, 0);
}
