/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:24:23 by frapp             #+#    #+#             */
/*   Updated: 2023/11/20 17:04:13 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_hor(t_line line, t_input *input, int *xi, int *yi)
{
	int				x;
	int				y;

	y = 0;
	while (y <= input->y_max)
	{
		x = 1;
		line.color.first = true;
		while (x <= input->x_max)
		{
			line.color.index = y * (input->x_max +1) + x;
			line.x1 = xi[line.color.index - 1];
			line.x2 = xi[line.color.index];
			line.y1 = yi[line.color.index - 1];
			line.y2 = yi[line.color.index];
			line.color.z_target =  input->all_pts[line.color.index * 3 + 2];
			line.last_color.z_target = input->all_pts[line.color.index * 3 + 2 - 3];
			connect_points(&line);
			x++;
			line.last_color = line.color;
			line.color.first = false;
		}
		y++;
	}
}

void	draw_vert(t_line line, t_input *input, int *xi, int *yi)
{
	int				x;
	int				y;

	x = 0;
	line.color.first = true;
	while (x <= input->x_max)
	{
		y = 1;
		while (y <= input->y_max)
		{
			line.color.index = y * (input->x_max +1) + x;
			line.x1 = xi[(y - 1) * (input->x_max +1) + x];
			line.x2 = xi[line.color.index];
			line.y1 = yi[(y - 1) * (input->x_max +1) + x];
			line.y2 = yi[line.color.index];
			line.color.z_target =  input->all_pts[line.color.index * 3 + 2];
			line.last_color.z_target =  input->all_pts[((y - 1) * (input->x_max +1) + x) * 3 + 2];
			connect_points(&line);
			line.last_color = line.color;
			y++;
		}
		line.color.first = false;
		x++;
	}
}

void	draw(t_window *window, t_input *input, int *xi, int *yi)
{
	t_line line;

	line.color.hex = input->hex;
	line.color.input = input;
	line.img = window->points->ptr;
	line.color.max_z = input->z_max;
	line.color.min_z = input->z_min;
	draw_hor(line, input, xi, yi);
	draw_vert(line, input, xi, yi);
}
