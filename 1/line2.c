/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:56:51 by frapp             #+#    #+#             */
/*   Updated: 2023/11/20 13:17:28 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_steep(t_line *line)
{
	double	when_other;

	when_other = line->l1;
	while (line->x1 != line->x2)
	{
		get_color(&(line->color), &(line->last_color));
		put_point(line->img, line->x1, line->y1, line->color.color);
		when_other -= line->l2;
		if (when_other < 0)
		{
			line->y1 += line->direct_y;
			when_other += line->l1;
		}
		line->x1 += line->direct_x;
	}
}

void	put_flat(t_line *line)
{
	double	when_other;

	when_other = line->l2;
	while (line->y1 != line->y2)
	{
		line->color.x_now = line->x1;
		line->color.y_now = line->y1;
		get_color(&(line->color), &(line->last_color));
		put_point(line->img, line->x1, line->y1, line->color.color);
		when_other -= line->l1;
		if (when_other < 0)
		{
			line->x1 += line->direct_x;
			when_other += line->l2;
		}
		line->y1 += line->direct_y;
	}
}

void	connect_points(t_line *line)
{
	line->color.x_start = line->x1;
	line->color.y_start = line->y1;
	line->color.x_target = line->x2;
	line->color.y_target = line->y2;
	line->l1 = abs(line->x2 - line->x1);
	line->l2 = abs(line->y2 - line->y1);
	set_color_fin_targets(line);
	if (line->x1 == line->x2 || line->y1 == line->y2)
		return (draw_straight_line(line));
	line->direct_x = 1;
	if (line->x1 > line->x2)
		line->direct_x = -1;
	line->direct_y = 1;
	if (line->y1 > line->y2)
		line->direct_y = -1;
	if (line->l1 > line->l2)
		put_steep(line);
	else if (line->l2 >= line->l1)
		put_flat(line);
	//get_color(&(line->color), &(line->last_color));
	//put_point(line->img, line->x2, line->y2, line->color.color);
}
