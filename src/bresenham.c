/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:59:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/28 12:03:21 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;
	
    if((x >= 0 && x < WINDOW_X) && (y >= 0 && y < WINDOW_Y))
    {
	offset = (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
    }
    return ;
}

void bresenham(t_vars *vars, int xA, int yA, int xB, int yB) {
    int dx = abs(xB - xA);
    int dy = abs(yB - yA);
    int sx = xA < xB ? 1 : -1;
    int sy = yA < yB ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (xA != xB || yA != yB) {
        my_mlx_pixel_put(&vars->bitmap, xA, yA, 0xFFFFF);
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            xA += sx;
        }
        if (e2 < dy) {
            err += dx;
            yA += sy;
        }
    }
    my_mlx_pixel_put(&vars->bitmap, xA, yA, 0xFFFFF);
}

void background(t_vars *vars)
{
    int x = 0;
    int y = 0;

    while(y < WINDOW_Y)
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

void connect_right(t_vars *vars, int x, int y, int xp, int yp, int offset_x, int offset_y)
{
    int xp_right;
    int yp_right;
    int z_right;
	if (vars->map[y][x + 1])
	{
        z_right = ft_atoi(vars->map[y][x + 1]);
		xp_right = (((x + 1) - y) * cos(vars->angle) * vars->scale) + offset_x;
		yp_right = ((((x + 1) + y) * sin(vars->angle))- z_right) * vars->scale + offset_y;
		bresenham(vars, xp, yp, xp_right, yp_right);
	}
}

void connect_down(t_vars *vars, int x, int y, int xp, int yp, int offset_x, int offset_y)
{
    int xp_down;
    int yp_down;
    int z_down;
	if (vars->map[y + 1])
	{
        z_down = ft_atoi(vars->map[y + 1][x]);
		xp_down = ((x - (y + 1)) * cos(vars->angle) * vars->scale) + offset_x;
		yp_down = ((((x + (y + 1)) * sin(vars->angle))- z_down) * vars->scale) + offset_y;
		bresenham(vars, xp, yp, xp_down, yp_down);
	}

}