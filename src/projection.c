/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:17:46 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/14 13:38:18 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	project_xy(t_vars *vars, t_point *p, double angle)
{
	p->xp = (p->x - p->y) * cos(angle) * vars->scale + vars->center_x;
	p->yp = ((p->x + p->y) * sin(angle) - p->z) * vars->scale + vars->center_y;
}
