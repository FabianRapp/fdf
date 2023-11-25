/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:56:51 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 21:32:44 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//if (!(line->x1 % GRAFIC_LVL))
void	put_steep(t_line *line, int i)
{
	int	when_other;

	when_other = line->l1;
	line->color.x_now = line->x1;
	line->color.y_now = line->y1;
	get_color(&(line->color));
	while (line->x1 != line->x2)
	{
		line->color.x_now = line->x1;
		line->color.y_now = line->y1;
		get_color(&(line->color));
		if (line->x1 < X_IM_SIZE && line->y1 < Y_IM_SIZE
			&& line->x1 >= 0 && line->y1 >= 0)
			((uint32_t *)(line->img->pixels))
			[i + line->x1] = line->color.color;
		when_other -= line->l2;
		if (when_other < 0)
		{
			line->y1 += line->direct_y;
			when_other += line->l1;
			i = X_IM_SIZE * line->y1;
		}
		line->x1 += line->direct_x;
	}
}

void	put_flat(t_line *line)
{
	int	when_other;

	when_other = line->l2;
	line->color.x_now = line->x1;
	line->color.y_now = line->y1;
	get_color(&(line->color));
	while (line->y1 != line->y2)
	{
		line->color.x_now = line->x1;
		line->color.y_now = line->y1;
		get_color(&(line->color));
		if (line->x1 < X_IM_SIZE && line->y1 < Y_IM_SIZE
			&& line->x1 >= 0 && line->y1 >= 0)
			((uint32_t *)(line->img->pixels))
			[X_IM_SIZE * line->y1 + line->x1] = line->color.color;
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
	if ((line->x1 > X_IM_SIZE && line->x2 > X_IM_SIZE)
		|| (line->x1 < 0 && line->x2 < 0) || (line->y1 < 0 && line->y2 < 0)
		|| (line->y1 > Y_IM_SIZE && line->y2 > Y_IM_SIZE))
		return ;
	line->color.x_start = line->x1;
	line->color.y_start = line->y1;
	line->color.x_target = line->x2;
	line->color.y_target = line->y2;
	if (line->x1 == line->x2 || line->y1 == line->y2)
		return (draw_straight_line(line));
	line->l1 = abs(line->x2 - line->x1);
	line->l2 = abs(line->y2 - line->y1);
	line->direct_x = 1;
	if (line->x1 > line->x2)
		line->direct_x = -1;
	line->direct_y = 1;
	if (line->y1 > line->y2)
		line->direct_y = -1;
	if (line->l1 > line->l2)
		put_steep(line, X_IM_SIZE * line->y1);
	else if (line->l2 >= line->l1)
		put_flat(line);
}
