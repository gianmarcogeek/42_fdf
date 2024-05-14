/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:01:03 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 15:35:39 by gpuscedd         ###   ########.fr       */
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

void	bresenham_pixel_put(t_data *data, t_line l)
{
	char	*dst;
	int		offset;

	if ((l.xp_curr >= 0 && l.xp_curr < WINDOW_X) \
		&& (l.yp_curr >= 0 && l.yp_curr < WINDOW_Y))
	{
		offset = (l.yp_curr * data->line_lenght + l.xp_curr \
					* (data->bits_per_pixel / 8));
		dst = data->addr + offset;
		*(unsigned int *) dst = l.color.trgb;
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
			my_mlx_pixel_put(&vars->bitmap, x, y, DEF_BACK_COLOR);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, 0, 0);
}

void	ft_error(char *message)
{
	ft_printf("\n\e[41m\e[1m Error! \e[0m %s\n\n", message);
	exit(1);
}
