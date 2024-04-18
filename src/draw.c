/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:10:33 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/04/18 19:13:40 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_line(t_data *data, int x_pos, int y_pos, int lenght, int color)
{
		int x_draw = x_pos;
		while((x_draw - x_pos) < lenght)
		{
			my_mlx_pixel_put(data, x_draw, y_pos, color);
			x_draw++;
		}
}
void	draw_faded_square(t_data *data, int x_pos, int y_pos, int side, int color_start, int color_end) //funziona un cazzo sotto i 256px
{
	int x_draw;
	int y_draw;

	int a_start = get_t(color_start);
	int r_start = get_r(color_start);
	int g_start = get_g(color_start);
	int b_start = get_b(color_start);

	int a_end = get_t(color_end);
	int r_end = get_r(color_end);
	int g_end = get_g(color_end);
	int b_end = get_b(color_end);

	int step_a = (a_end - a_start) / side;
	int step_r = (r_end - r_start) / side;
	int step_g = (g_end - g_start) / side;
	int step_b = (b_end - b_start) / side;

	y_draw = y_pos;

	while((y_draw - y_pos) < side)
	{
		int color = create_trgb((a_start + (y_draw - y_pos) * step_a), (r_start + (y_draw - y_pos) * step_r), \
		(g_start + (y_draw - y_pos) * step_g), (g_start + (y_draw - y_pos) * step_g));

		draw_line(data, x_pos, y_draw, side, color);
		y_draw++;
	}

}

void	draw_square(t_data *data, int x_pos, int y_pos, int side, int color)
{
	int x_draw;
	int y_draw;

	y_draw = y_pos;

	while((y_draw - y_pos) < side)
	{
		draw_line(data, x_pos, y_draw, side, color);
		y_draw++;
	}
}

