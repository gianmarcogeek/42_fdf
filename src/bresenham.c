/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:59:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 13:25:11 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static	void	determine_slope(t_vars *vars, t_point end)
{
	if (vars->point.xp < end.xp)
		vars->line.sx = 1;
	else
		vars->line.sx = -1;
	if (vars->point.yp < end.yp)
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
	vars->line.xp_curr = vars->point.xp;
	vars->line.yp_curr = vars->point.yp;
	vars->line.color.trgb = vars->point.color.trgb;
	vars->line.dx = abs(end.xp - vars->line.xp_curr);
	vars->line.dy = abs(end.yp - vars->line.yp_curr);
	determine_slope(vars, end);
	determine_err(vars->line.dx, vars->line.dy, &vars->line.err);
	while (vars->line.xp_curr != end.xp || vars->line.yp_curr != end.yp)
	{
		vars->line.color = lerp_trgb(vars->line.color, end.color, LERP_STEP);
		bresenham_pixel_put(&vars->bitmap, vars->line);
		vars->line.e2 = vars->line.err;
		if (vars->line.e2 > -vars->line.dx)
		{
			vars->line.err -= vars->line.dy;
			vars->line.xp_curr += vars->line.sx;
		}
		if (vars->line.e2 < vars->line.dy)
		{
			vars->line.err += vars->line.dx;
			vars->line.yp_curr += vars->line.sy;
		}
	}
	bresenham_pixel_put(&vars->bitmap, vars->line);
}

void	connect_right(t_vars *vars)
{
	vars->p_right.x = vars->point.x + 1;
	vars->p_right.y = vars->point.y;
	if (vars->map[vars->p_right.y][vars->p_right.x])
	{
		vars->p_right.z = ft_atoi(vars->map[vars->p_right.y][vars->p_right.x]);
		parse_color(vars, &vars->p_right);
		project_xy(vars, &vars->p_right, ANGLE);
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
		parse_color(vars, &vars->p_down);
		project_xy(vars, &vars->p_down, ANGLE);
		bresenham(vars, vars->p_down);
	}
}
