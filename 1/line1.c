/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:19:48 by frapp             #+#    #+#             */
/*   Updated: 2023/11/20 13:16:25 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_horizonatl_line(t_line *line)
{
	int		current;
	int		start;
	int		end;

	if (line->x1 < line->x2)
	{
		start = line->x1;
		end = line->x2;
	}
	else
	{
		start = line->x2;
		end = line->x1;
	}
	current = start;
	while (current <= end)
	{
		line->color.x_now = current;
		line->color.y_now = line->y1;
		get_color(&(line->color), &(line->last_color));
		put_point(line->img, current++, line->y1, line->color.color);
	}
}

void	put_vertical_line(t_line *line)
{
	int		current;
	int		start;
	int		end;

	if (line->y1 < line->y2)
	{
		start = line->y1;
		end = line->y2;
	}
	else
	{
		start = line->y2;
		end = line->y1;
	}
	current = start;
	while (current <= end)
	{
		line->color.x_now = line->x1;
		line->color.y_now = current;
		get_color(&(line->color), &(line->last_color));
		put_point(line->img, line->x1, current++, line->color.color);
	}
}

void	draw_straight_line(t_line *line)
{
	if (line->x1 == line->x2)
		put_vertical_line(line);
	else if (line->y1 == line->y2)
		put_horizonatl_line(line);
}
