/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:24:23 by frapp             #+#    #+#             */
/*   Updated: 2023/12/30 23:02:58 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_hor(t_line line, t_input *input, int *prj_x, int *prj_y)
{
	int				x;
	int				y;

	y = 0;
	while (y <= input->y_max)
	{
		x = 1;
		while (x <= input->x_max)
		{
			line.index = y * (input->x_max +1) + x;
			line.x1 = prj_x[line.index - 1];
			line.x2 = prj_x[line.index];
			line.y1 = prj_y[line.index - 1];
			line.y2 = prj_y[line.index];
			line.color.z_target = input->all_pts[line.index * 3 + 2];
			line.color.last_z_target = input->all_pts[
				line.index * 3 + 2 - 3];
			connect_points(&line);
			x++;
		}
		y++;
	}
}

void	draw_vert(t_line line, t_input *input, int *prj_x, int *prj_y)
{
	int				x;
	int				y;

	x = 0;
	while (x <= input->x_max)
	{
		y = 1;
		while (y <= input->y_max)
		{
			line.index = y * (input->x_max +1) + x;
			line.x1 = prj_x[(y - 1) * (input->x_max +1) + x];
			line.x2 = prj_x[line.index];
			line.y1 = prj_y[(y - 1) * (input->x_max +1) + x];
			line.y2 = prj_y[line.index];
			line.color.z_target = input->all_pts[line.index * 3 + 2];
			line.color.last_z_target = input->all_pts[
				((y - 1) * (input->x_max +1) + x) * 3 + 2];
			connect_points(&line);
			y++;
		}
		x++;
	}
}

void	draw(t_window *window, t_input *input, int *prj_x, int *prj_y)
{
	t_line	line;

	init_rgba(&line.color);
	line.img = window->img.ptr;
	line.color.min_displayed_z = window->min_displayed_z;
	line.color.max_z = input->z_max;
	line.color.min_z = input->z_min;
	draw_hor(line, input, prj_x, prj_y);
	draw_vert(line, input, prj_x, prj_y);
}
