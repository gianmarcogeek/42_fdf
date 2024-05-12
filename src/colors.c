/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:31:34 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/13 01:19:38 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	create_trgb(t_color color)
{
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

void split_trgb(t_color *color)
{
	color->t = (color->trgb >> 24) & 0xFF;
	color->r = (color->trgb >> 16) & 0xFF;
	color->g = (color->trgb >> 8) & 0xFF;
	color->b = color->trgb & 0xFF;
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

t_color	calculate_color(t_color A, t_color B, float t)
{
	t_color new_color;
	
	split_trgb(&A);
	split_trgb(&B);

	new_color.t =  A.t + (B.t - A.t) * t;
	new_color.r =  A.r + (B.r - A.r) * t;
	new_color.g =  A.g + (B.g - A.g) * t;
	new_color.b =  A.b + (B.b - A.b) * t;
	new_color.trgb = create_trgb(new_color);

	return(new_color);
	
}