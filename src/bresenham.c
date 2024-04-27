/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:59:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/27 16:23:42 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;
	
	offset = (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

void bresenham(t_vars *vars, int A_x, int A_y, int B_x, int B_y)
{
    int dx = abs(B_x - A_x);
    int dy = abs(B_y - A_y);

    int decision;
    if (dx >= dy)
    {
        decision = 2 * dy - dx;
    }
    else {
        decision = 2 * dx - dy;
    }

    int x = A_x;
    int y = A_y;
    my_mlx_pixel_put(&vars->bitmap, x, y, 0xFFFFFF);

    int s = 1;
    int q = 1;

    if (B_x < A_x)
        q = -1;
    if (B_y < A_y)
        s = -1;

    while (x != B_x || y != B_y)
    {
        if (dx >= dy)
        {
            if (decision >= 0)
            {
                decision += 2 * (dy - dx);
                y += s;
            }
            decision += 2 * dy;
            x += q;
        }
        else
        {
            if (decision >= 0)
            {
                decision += 2 * (dx - dy);
                x += q;
            }
            decision += 2 * dx;
            y += s;
        }
        my_mlx_pixel_put(&vars->bitmap, x, y, 0xFFFFFF);
    }
}
