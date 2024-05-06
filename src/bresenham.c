/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:59:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/06 23:10:53 by gpuscedd         ###   ########.fr       */
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

void	bresenham(t_vars *vars, int xB, int yB) //porcoddio norminette
{
	t_line	line;
	int xA;
	int yA;

	xA = vars->point.xp;
	yA = vars->point.yp;
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

void	connect_right(t_vars *vars)
{
	t_point p_right;

	p_right.x = vars->point.x + 1;
	p_right.y = vars->point.y;
	if (vars->map[p_right.y][p_right.x])
	{
		p_right.z = ft_atoi(vars->map[p_right.y][p_right.x]);
		p_right.xp = ((p_right.x - p_right.y) * cos(vars->angle) * vars->scale) + vars->center_x;
		p_right.yp = (((p_right.x + p_right.y) * sin(vars->angle)) - p_right.z) * vars->scale + vars->center_y;
		bresenham(vars, p_right.xp, p_right.yp);
	}
}

void	connect_down(t_vars *vars)
{
	t_point p_down;
	
	p_down.x = vars->point.x;
	p_down.y = vars->point.y + 1;
	if (vars->map[p_down.y])
	{
		p_down.z = ft_atoi(vars->map[p_down.y][p_down.x]);
		p_down.xp = ((p_down.x - p_down.y) * cos(vars->angle) * vars->scale) + vars->center_x;
		p_down.yp = (((p_down.x + p_down.y) * sin(vars->angle)) - p_down.z) * vars->scale + vars->center_y;
		bresenham(vars, p_down.xp, p_down.yp);
	}
}
