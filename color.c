/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:54:24 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 20:32:08 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// uint32_t	get_rgba(double progress, t_color *color)
// {
// 	if (fabs(progress) < 0.5)
// 	{
// 		if (color->z_now > 0)
// 			color->rgba = &color->rgba4;
// 		else
// 			color->rgba = &color->rgba2;
// 		progress *= 2;
// 	}
// 	else
// 	{
// 		if (color->z_now > 0)
// 			color->rgba = &color->rgba3;
// 		else
// 			color->rgba = &color->rgba1;
// 		progress -= 0.5;
// 		progress *= 2;
// 	}
// 	color->rgba->red = (uint8_t)((1 - progress)
// 			* color->rgba->start_red + progress * color->rgba->end_red);
// 	color->rgba->green = (uint8_t)((1 - progress)
// 			* color->rgba->start_green + progress * color->rgba->end_green);
// 	color->rgba->blue = (uint8_t)((1 - progress)
// 			* color->rgba->start_blue + progress * color->rgba->end_blue);
// 	return ((color->rgba->red)
// 		| (color->rgba->green << 8) | (color->rgba->blue << 16) | 0xFF << 24);
// 	// return ((color->rgba->red << 16)
// 	// 	| (color->rgba->green << 8) | (color->rgba->blue));
// }

// double	pyt(int x1, int x2, int y1, int y2)
// {
// 	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
// }

// void	get_color(t_color *color)
// {
// 	double		progress;
// 	int			z_diff;
// 	double		total_dist_2d;
// 	double		cur_dist_2d;

// 	total_dist_2d = pyt(color->x_start, color->x_target,
// 			color->y_start, color->y_target);
// 	cur_dist_2d = pyt(color->x_start, color->x_now,
// 			color->y_start, color->y_now);
// 	if (total_dist_2d)
// 		progress = cur_dist_2d / total_dist_2d;
// 	else
// 		progress = 1;
// 	z_diff = (color->z_target - color->last_z_target);
// 	color->z_now = z_diff * progress + color->last_z_target;
// 	if (color->z_now < 0)
// 		progress = (color->z_now / color->min_z);
// 	else if (color->z_now > 0)
// 		progress = (color->z_now / color->max_z);
// 	else
// 		progress = 0;
// 	color->color = get_rgba(progress, color);
// }

uint32_t	get_rgba(float progress, t_color *color)
{
	if (progress < 0.5)
	{
		if (color->z_now > 0)
			color->rgba = &color->rgba4;
		else
			color->rgba = &color->rgba2;
		progress *= 2;
	}
	else
	{
		if (color->z_now > 0)
			color->rgba = &color->rgba3;
		else
			color->rgba = &color->rgba1;
		progress -= 0.5;
		progress *= 2;
	}
	color->rgba->red = (uint8_t)((1 - progress)
			* color->rgba->start_red + progress * color->rgba->end_red);
	color->rgba->green = (uint8_t)((1 - progress)
			* color->rgba->start_green + progress * color->rgba->end_green);
	color->rgba->blue = (uint8_t)((1 - progress)
			* color->rgba->start_blue + progress * color->rgba->end_blue);
	return ((color->rgba->red)
		| (color->rgba->green << 8) | (color->rgba->blue << 16) | 0xFF << 24);
}

void	get_color(t_color *color)
{
	float		progress;
	int			z_diff;
	int			total_dist_2d;
	int			cur_dist_2d;

	total_dist_2d = (color->x_start - color->x_target)
		* (color->x_start - color->x_target)
		+ (color->y_start - color->y_target)
		* (color->y_start - color->y_target);
	cur_dist_2d = (color->x_start - color->x_now)
		* (color->x_start - color->x_now)
		+ (color->y_start - color->y_now) * (color->y_start - color->y_now);
	if (total_dist_2d)
		progress = (float)cur_dist_2d / total_dist_2d;
	else
		progress = 1.0;
	z_diff = (color->z_target - color->last_z_target);
	color->z_now = z_diff * progress + color->last_z_target;
	if (color->z_now > 0)
		progress = (color->z_now / color->max_z);
	else if (color->z_now < 0)
		progress = (color->z_now / color->min_z);
	else
		progress = 0;
	color->color = get_rgba(progress, color);
}
