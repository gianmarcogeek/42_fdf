/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:01:03 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/13 18:21:29 by gpuscedd         ###   ########.fr       */
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
			my_mlx_pixel_put(&vars->bitmap, x, y, DEF_BACK_COLOR);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->bitmap.img, 0, 0);
}

void display_istructions(void)
{
	ft_printf("\e[1m\e[42m Change view \e[0m\n");
	ft_printf("\e[1m|-\e[0m translate with arrows\n");
	ft_printf("\e[1m|-\e[0m zoom with [+] / [-]\n");
	ft_printf("\e[1m|-\e[0m reset position [0]\n");
	ft_printf("\e[1m\n");
}

void	ft_error(char *message)
{
	ft_printf("\n\e[41m\e[1m Error! \e[0m %s\n\n", message);
	exit(1);
}