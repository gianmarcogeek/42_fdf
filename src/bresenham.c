/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:59:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/28 00:17:45 by gpuscedd         ###   ########.fr       */
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

// void bresenham(t_vars *vars, int A_x, int A_y, int B_x, int B_y)
// {
//     int dx = abs(B_x - A_x);
//     int dy = abs(B_y - A_y);

//     int decision;
//     if (dx >= dy)
//     {
//         decision = 2 * dy - dx;
//     }
//     else 
//     {
//         decision = 2 * dx - dy;
//     }

//     int x = A_x;
//     int y = A_y;
//     my_mlx_pixel_put(&vars->bitmap, x, y, 0xFFFFFF);

//     int s = 1;
//     int q = 1;

//     if (B_x < A_x)
//         q = -1;
//     if (B_y < A_y)
//         s = -1;

//     while (x != B_x && y != B_y)
//     {
//         if (dx >= dy)
//         {
//             if (decision >= 0)
//             {
//                 decision += 2 * (dy - dx);
//                 y += s;
//             }
//             decision += 2 * dy;
//             x += q;
//         }
//         else
//         {
//             if (decision >= 0)
//             {
//                 decision += 2 * (dx - dy);
//                 x += q;
//             }
//             decision += 2 * dx;
//             y += s;
//         }
//         my_mlx_pixel_put(&vars->bitmap, x, y, 0xFFFFFF);
//     }
// }

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
    my_mlx_pixel_put(&vars->bitmap, xA, yA, 0xFFFFF);// Stampa il punto finale
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