/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:19:48 by frapp             #+#    #+#             */
/*   Updated: 2023/11/11 02:37:58 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_horizonatl_line(t_line *struc)
{
	int		current;
	int		start;
	int		end;

	if (struc->x1 < struc->x2)
	{
		start = struc->x1;
		end = struc->x2;
	}
	else
	{
		start = struc->x2;
		end = struc->x1;
	}
	current = start;
	while (current <= end)
	{
		if (struc->get_col)
			struc->color.color = COLOR_BASE;
		put_point(struc->img, current++, struc->y1, struc->color.color);
	}
}

void	put_vertical_line(t_line *struc)
{
	int		current;
	int		start;
	int		end;

	if (struc->y1 < struc->y2)
	{
		start = struc->y1;
		end = struc->y2;
	}
	else
	{
		start = struc->y2;
		end = struc->y1;
	}
	current = start;
	while (current <= end)
	{
		if (struc->get_col)
			struc->color.color = COLOR_BASE;
		put_point(struc->img, struc->x1, current++, struc->color.color);
	}
}

void	draw_straight_line(t_line *struc)
{
	if (struc->x1 == struc->x2)
		put_vertical_line(struc);
	else if (struc->y1 == struc->y2)
		put_horizonatl_line(struc);
}
