/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:19:48 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 21:16:08 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_horizonatl_line(t_line *line)
{
	int		current;
	int		end;

	current = line->x2;
	end = line->x1;
	if (line->x1 < line->x2)
	{
		current = line->x1;
		end = line->x2;
	}
	line->color.x_now = current;
	line->color.y_now = line->y1;
	get_color(&(line->color));
	while (current <= end)
	{
		line->color.x_now = ++current - 1;
		line->color.y_now = line->y1;
		get_color(&(line->color));
		if (line->color.z_now >= line->color.min_displayed_z
			&& current < X_IM_SIZE && line->y1 < Y_IM_SIZE
			&& current >= 0 && line->y1 >= 0)
			((uint32_t *)(line->img->pixels))
			[X_IM_SIZE * line->y1 + current] = line->color.color;
	}
}

void	put_vertical_line(t_line *line)
{
	int		current;
	int		end;

	current = line->y2;
	end = line->y1;
	if (line->y1 < line->y2)
	{
		current = line->y1;
		end = line->y2;
	}
	line->color.x_now = line->x1;
	line->color.y_now = current;
	get_color(&(line->color));
	while (current <= end)
	{
		line->color.x_now = line->x1;
		line->color.y_now = ++current - 1;
		get_color(&(line->color));
		if (line->color.z_now >= line->color.min_displayed_z
			&& line->x1 < X_IM_SIZE && current < Y_IM_SIZE
			&& line->x1 >= 0 && current >= 0)
			((uint32_t *)(line->img->pixels))
			[X_IM_SIZE * current + line->x1] = line->color.color;
	}
}

void	draw_straight_line(t_line *line)
{
	if (line->x1 == line->x2)
		put_vertical_line(line);
	else if (line->y1 == line->y2)
		put_horizonatl_line(line);
}
