/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:56:51 by frapp             #+#    #+#             */
/*   Updated: 2023/11/11 02:42:31 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_steep(t_line *struc)
{
	double	when_other;

	when_other = struc->l1;
	while (struc->x1 != struc->x2)
	{
		if (struc->get_col)
			struc->color.color = COLOR_BASE;
		put_point(struc->img, struc->x1, struc->y1, struc->color.color);
		when_other -= struc->l2;
		if (when_other < 0)
		{
			struc->y1 += struc->direct_y;
			when_other += struc->l1;
		}
		struc->x1 += struc->direct_x;
	}
}

void	put_flat(t_line *struc)
{
	double	when_other;

	when_other = struc->l2;
	while (struc->y1 != struc->y2)
	{
		if (struc->get_col)
			struc->color.color = COLOR_BASE;
		put_point(struc->img, struc->x1, struc->y1, struc->color.color);
		when_other -= struc->l1;
		if (when_other < 0)
		{
			struc->x1 += struc->direct_x;
			when_other += struc->l2;
		}
		struc->y1 += struc->direct_y;
	}
}

void	connect_points(t_line *struc)
{
	struc->l1 = abs(struc->x2 - struc->x1);
	struc->l2 = abs(struc->y2 - struc->y1);
	if (struc->x1 == struc->x2 || struc->y1 == struc->y2)
		return (draw_straight_line(struc));
	struc->direct_x = 1;
	if (struc->x1 > struc->x2)
		struc->direct_x = -1;
	struc->direct_y = 1;
	if (struc->y1 > struc->y2)
		struc->direct_y = -1;
	if (struc->l1 > struc->l2)
		put_steep(struc);
	else if (struc->l2 >= struc->l1)
		put_flat(struc);
	if (struc->get_col)
		struc->color.color = COLOR_BASE;
	put_point(struc->img, struc->x2, struc->y2, struc->color.color);
}
