/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:59:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/07 19:11:05 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static	void	determine_slope(int xA, int yA, t_vars *vars, t_point end)
{
	if (xA < end.xp)
		vars->line.sx = 1;
	else
		vars->line.sx = -1;
	if (yA < end.yp)
		vars->line.sy = 1;
	else
		vars->line.sy = -1;
}

static	void	determine_err(int dx, int dy, int *err)
{
	if (dx > dy)
		*err = dx / 2;
	else
		*err = -dy / 2;
}

void	bresenham(t_vars *vars, t_point end)
{
	int xA;
	int yA;

	xA = vars->point.xp;
	yA = vars->point.yp;
	vars->line.dx = abs(end.xp - xA);
	vars->line.dy = abs(end.yp - yA);
	determine_slope(xA, yA, vars, end);
	determine_err(vars->line.dx, vars->line.dy, &vars->line.err);
	while (xA != end.xp || yA != end.yp)
	{
		my_mlx_pixel_put(&vars->bitmap, xA, yA, 0xFFFFF);
		vars->line.e2 = vars->line.err;
		if (vars->line.e2 > -vars->line.dx)
		{
			vars->line.err -= vars->line.dy;
			xA += vars->line.sx;
		}
		if (vars->line.e2 < vars->line.dy)
		{
			vars->line.err += vars->line.dx;
			yA += vars->line.sy;
		}
	}
	my_mlx_pixel_put(&vars->bitmap, xA, yA, 0xFFFFF);
}

void	connect_right(t_vars *vars)
{
	vars->p_right.x = vars->point.x + 1;
	vars->p_right.y = vars->point.y;
	if (vars->map[vars->p_right.y][vars->p_right.x])
	{
		vars->p_right.z = ft_atoi(vars->map[vars->p_right.y][vars->p_right.x]);
		vars->p_right.xp = ((vars->p_right.x - vars->p_right.y) * cos(vars->angle) * vars->scale) + vars->center_x;
		vars->p_right.yp = (((vars->p_right.x + vars->p_right.y) * sin(vars->angle)) - vars->p_right.z) * vars->scale + vars->center_y;
		bresenham(vars, vars->p_right);
	}
}

void	connect_down(t_vars *vars)
{
	vars->p_down.x = vars->point.x;
	vars->p_down.y = vars->point.y + 1;
	if (vars->map[vars->p_down.y])
	{
		vars->p_down.z = ft_atoi(vars->map[vars->p_down.y][vars->p_down.x]);
		vars->p_down.xp = ((vars->p_down.x - vars->p_down.y) * cos(vars->angle) * vars->scale) + vars->center_x;
		vars->p_down.yp = (((vars->p_down.x + vars->p_down.y) * sin(vars->angle)) - vars->p_down.z) * vars->scale + vars->center_y;
		bresenham(vars, vars->p_down);
	}
}
