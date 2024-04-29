/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:59:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/29 11:09:03 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static	void	determine_slope(int xA, int xB, int yA, int yB, int *sx, int *sy)
{
	if (xA < xB)
		*sx = 1;
	else
		*sx = -1;
	if (yA < yB)
		*sy = 1;
	else
		*sy = -1;
}

static	void	determine_err(int dx, int dy, int *err)
{
	if (dx > dy)
		*err = dx / 2;
	else
		*err = -dy / 2;
}

void	bresenham(t_vars *vars, int xA, int yA, int xB, int yB)
{
	t_line	line;

	line.dx = abs(xB - xA);
	line.dy = abs(yB - yA);
	determine_slope(xA, xB, yA, yB, &line.sx, &line.sy);
	determine_err(line.dx, line.dy, &line.err);
	while (xA != xB || yA != yB)
	{
		my_mlx_pixel_put(&vars->bitmap, xA, yA, 0xFFFFF);
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			xA += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			yA += line.sy;
		}
	}
	my_mlx_pixel_put(&vars->bitmap, xA, yA, 0xFFFFF);
}

void	connect_right(t_vars *vars, int x, int y, int xp, int yp, int offset_x, int offset_y)
{
	int	xp_right;
	int	yp_right;
	int	z_right;

	if (vars->map[y][x + 1])
	{
		z_right = ft_atoi(vars->map[y][x + 1]);
		xp_right = (((x + 1) - y) * cos(vars->angle) * vars->scale) + offset_x;
		yp_right = ((((x + 1) + y) * sin(vars->angle)) - z_right) * vars->scale + offset_y;
		bresenham(vars, xp, yp, xp_right, yp_right);
	}
}

void	connect_down(t_vars *vars, int x, int y, int xp, int yp, int offset_x, int offset_y)
{
	int	xp_down;
	int	yp_down;
	int	z_down;

	if (vars->map[y + 1])
	{
		z_down = ft_atoi(vars->map[y + 1][x]);
		xp_down = ((x - (y + 1)) * cos(vars->angle) * vars->scale) + offset_x;
		yp_down = ((((x + (y + 1)) * sin(vars->angle)) - z_down) * vars->scale) + offset_y;
		bresenham(vars, xp, yp, xp_down, yp_down);
	}
}
