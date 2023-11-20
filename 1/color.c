/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:54:24 by frapp             #+#    #+#             */
/*   Updated: 2023/11/20 17:02:07 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//0xRRGGBBAA
#define WHITE 0xFFFFFFFF
#define BLUE 0x0000FFFF
#define MIN_BLUE 0x00000FFF
#define RED 0xFF0000FF
#define MIN_RED 0x0F0000FF
#define GREEN 0x00FF00FF
#define MIN_GREEN 0x000F00FF
#define YELLOW 0xFFFF00FF


#define	MAX_POSITIVE_COL 0xFFFF00FF
#define	MIN_POSITIVE_COL 0x000F00FF
#define	MAX_NEGATIVE_COL 0x0000FFFF
#define	MIN_NEGATIVE_COL 0x00000FFF

void	set_color_fin_targets(t_line *line)
{
	double	progress_to_max;

	if (line->color.z_target > 0)
	{
		progress_to_max = line->color.z_target / line->color.max_z;
		line->color.color_target = (unsigned)((MAX_POSITIVE_COL - MIN_POSITIVE_COL) * progress_to_max) + MIN_POSITIVE_COL;
		if (line->color.z_target == line->color.max_z)
			line->color.color_target = MAX_POSITIVE_COL;
		//line->color.color_target = MAX_POSITIVE_COL; /////////
	}
	else if (line->color.z_target < 0)
	{
		progress_to_max = fabs(((double)line->color.z_target) / line->color.min_z);
		line->color.color_target = (unsigned)((MAX_NEGATIVE_COL - MIN_NEGATIVE_COL) * progress_to_max) + MIN_NEGATIVE_COL;
		if (line->color.z_target == line->color.max_z)
			line->color.color_target = MAX_NEGATIVE_COL;
	}
	if (line->color.first)
	{
		if (line->last_color.z_target > 0)
		{
			progress_to_max = line->last_color.z_target / line->last_color.max_z;
			line->last_color.color_target = (unsigned)((MAX_POSITIVE_COL - MIN_POSITIVE_COL) * progress_to_max) + MIN_POSITIVE_COL;
			if (line->last_color.z_target == line->last_color.max_z)
				line->last_color.color_target = MAX_POSITIVE_COL;
			line->last_color.color = line->last_color.color_target;
		}
		else if (line->last_color.z_target < 0)
		{
			progress_to_max = fabs(((double)line->last_color.z_target) / line->last_color.min_z);
			line->last_color.color_target = (unsigned)((MAX_NEGATIVE_COL - MIN_NEGATIVE_COL) * progress_to_max) + MIN_NEGATIVE_COL;
			if (line->last_color.z_target == line->last_color.max_z)
				line->last_color.color_target = MAX_NEGATIVE_COL;
			line->last_color.color = line->last_color.color_target;
		}
	}
}

int	get_direc_z(t_color *color, t_color *last_color)
{
	return (1);
}

bool	edge_cases(t_color *color, t_color *last_color)
{
	if (color->first && !color->z_target && !color->hex)
	{
		color->color = WHITE;
		return (true);
	}
	if (!color->z_target && !last_color->z_target)
	{
		color->color = WHITE;
		return (true);
	}
	if (!color->first && (color->z_target == last_color->z_target))
	{
		color->color = last_color->color;
		return (true);
	}
	if (color->hex)
	{
		//color->color_target = color->input->colors[color->index];
		color->color = color->input->colors[color->index];
		return (true);
	}

	// if (!color->first && (color->z_target == last_color->z_target))
	// {
	// 	color->color = last_color->color;
	// 	return (true);
	// }
	return (false);
}

bool	set_locals(unsigned *local_color_start, unsigned *local_color_target, unsigned current_z, t_color *color, t_color *last_color)
{
	if (current_z > 0 && last_color->z_target > 0)
	{
	}
	if (current_z < 0 && last_color->z_target < 0)
	{
	}
	if (current_z < 0 && last_color->z_target > 0)
	{
	}
	if (current_z > 0 && last_color->z_target < 0)
	{
	}
	return (true);
}

double normalize(float value) {
	if (value == 1.0f) {
		return 1.0f;
	}
	value = fmodf(value, 1.0f);
	if (value < 0.0f) {
		value += 1.0f;
	}
	return value;
}

uint32_t getRGBA(double value, t_color *color, t_color *last_color)
{
	//value = normalize(value);
	if (value < 0.0f || value > 1.0f)
		printf("val: %f\n", value);

	uint8_t startRed = *((uint8_t *)&(last_color->color_target) + 0);
	uint8_t startGreen = *((uint8_t *)&(last_color->color_target) + 1);
	uint8_t startBlue = *((uint8_t *)&(last_color->color_target) + 2);
	uint8_t endRed = ((uint8_t *)&(color->color_target))[0];
	uint8_t endGreen = ((uint8_t *)&(color->color_target))[0];
	uint8_t endBlue = ((uint8_t *)&(color->color_target))[0];

	// uint8_t startRed = 255;
	// uint8_t startGreen = 255;
	// uint8_t startBlue = 255;
	// uint8_t endRed = ((uint8_t *)&(color->color_target))[0];
	// uint8_t endGreen = ((uint8_t *)&(color->color_target))[0];
	// uint8_t endBlue = ((uint8_t *)&(color->color_target))[0];


	// uint8_t startRed = 0xFF;
	// uint8_t startGreen = 0xFF;
	// uint8_t startBlue = 0xFF;
	// uint8_t endRed = 0x00;
	// uint8_t endGreen = 0x00;
	// uint8_t endBlue = 0x00;

	//Calculate intermediate color
	uint8_t red = (uint8_t)((1 - value) * startRed - value * endRed);
	uint8_t green = (uint8_t)((1 - value) * startGreen - value * endGreen);
	uint8_t blue = (uint8_t)((1 - value) * startBlue - value * endBlue);
	uint8_t alpha = 255; // Fully opaque

	// uint8_t red = (uint8_t)((1 - value) * startRed + value * endRed);
	// // uint8_t green = (uint8_t)((1 - value) * startGreen + value * endGreen);
	// // uint8_t blue = (uint8_t)((1 - value) * startBlue + value * endBlue);
	// uint8_t green = 255;
	// uint8_t blue = 255;
	// uint8_t alpha = 255; // Fully opaque

	// Combine into a single 32-bit integer
	uint32_t rgba = (red << 24) | (green << 16) | (blue << 8) | alpha;
	return rgba;
}

void	get_color(t_color *color, t_color *last_color)
{
	double		cur_z;
	double		progress;
	double		progress_to_max;
	unsigned	local_color_target;
	unsigned	local_color_start;
	unsigned	color_diff;
	unsigned	col_dist;
	int			start_z;
	int			target_z;

	//if (edge_cases(color, last_color))
	//	return ;
	double total_dist_2d = fabs(pyt(color->x_start, color->x_target, color->y_start, color->y_target));
	double cur_dist_2d = fabs(pyt(color->x_start, color->x_now, color->y_start, color->y_now));
	if (total_dist_2d)
		progress = cur_dist_2d / total_dist_2d;
	else
	{
		progress = 1;
		printf("0 dist?\n");
	}
	if (progress < 0.00001 && progress > -0.0001)
		progress = 0;

	int z_diff = abs(color->z_target - last_color->z_target);
	cur_z = z_diff * progress + last_color->z_target;
	if (cur_z < 0)
	{
		
		progress = cur_z / color->min_z;
	}
	else if (cur_z > 0)
	{
		progress = cur_z / color->max_z;
	}
	else
		progress = 0;
	//if (!color->max_z)
	//	progress = 0;
	if (progress < 0.00001 && progress > -0.0001)
		progress = 0;
	color->color = getRGBA(progress, color, last_color);
	//else
	//	color->color = getRGBA(progress, color, last_color);
	// else if (color->z_target < last_color->z_target)
	// {
	// 	color->color = getRGBA(progress, last_color, color);
	// 	color->color = last_color->color;
	// }
	// if (color->z_target > 0 && last_color->z_target > 0)
	// {
	// 	local_color_target = color->color_target;///////
	// 	local_color_start = last_color->color;///////////
	// 	if (color->z_target > last_color->z_target)
	// 	{
	// 		col_dist = local_color_target - local_color_start;
	// 		if (progress < 0.7)
	// 			printf("%x\n", local_color_target - local_color_start);
	// 		color->color = (unsigned)(round((col_dist * progress + local_color_start)));
	// 		//color->color = local_color_target;
	// 	}
	// 	else
	// 	{
	// 		col_dist = local_color_start - local_color_target;
	// 		if (progress < 0.7)
	// 			printf("%x\n", local_color_target - local_color_start);
	// 		color->color = (unsigned)(round((-(col_dist * progress) + local_color_start)));
	// 		//color->color = local_color_target;
	// 	}
	// }
	// else if (color->z_target < 0 && last_color->z_target < 0)
	// {
	// 	printf("1\n");
	// }
	// else if (color->z_target < 0 && last_color->z_target > 0)
	// {
	// 	printf("2\n");
	// }
	// else if (color->z_target > 0 && last_color->z_target < 0)
	// {
	// 	printf("3\n");
	// }
	// //else
	// {
	// 	if (color->z_target && last_color->z_target)
	// 		printf("here: %d;  %d\n", color->z_target, last_color->z_target);
	// }




	// //if (!set_locals(&local_color_start, &local_color_target, cur_z, color, last_color))
	// //	return ;
	// if (z_diff > 0)
	// {
	// 	local_color_target = color->color_target;///////
	// 	local_color_start = last_color->color;///////////
	// 	if (cur_z > 0)
	// 	{
	// 		if (progress < 0.7)
	// 			printf("%x\n", local_color_target - local_color_start);
	// 		color->color = (unsigned)(round(((local_color_target - local_color_start) * progress + local_color_start)));
	// 		//color->color = local_color_target;
	// 	}
	// }
	// else if (z_diff < 0)
	// {
	// 	local_color_start = color->color_target;///////
	// 	local_color_target = last_color->color;///////////
	// 	if (cur_z > 0)
	// 	{
	// 		if (progress < 0.7)
	// 			printf("%x\n", local_color_target - local_color_start);
	// 		color->color = (unsigned)(round(((local_color_target - local_color_start) * progress + local_color_start)));
	// 		//color->color = local_color_target;
	// 	}
	// }
	// else
	// {
	// 	printf("no z diff\n");
	// 	return ;
	// }
	// if (cur_z < 0.0001 && cur_z > -0.0001)
	// 	color->color = WHITE;
	// // does not handle z target <= 0

}
