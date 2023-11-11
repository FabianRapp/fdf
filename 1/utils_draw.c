/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:29:36 by frapp             #+#    #+#             */
/*   Updated: 2023/11/11 02:44:21 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// #define BASE_COLOR 0xFFFFFFFF

// unsigned int	get_color(t_input *input, int index, unsigned int last_color)
// {
// 	unsigned int	color;

// 	static int counter = 0;

// 	color = BASE_COLOR;
// 	if (last_color && last_color != 1)
// 	{
// 		if (color < last_color)
// 			color = last_color;
// 	}
// 	else if (last_color == 1)
// 	{
// 		counter++;
// 		if (input->all_pts[(index - input->y_max) * 3 + 2] > input->all_pts[index * 3 + 2])
// 		{
// 			color += input->all_pts[(index - input->y_max) * 3 + 2] * 0x000FFFFF;
// 			printf("z val: %d\n",input->all_pts[(index - input->y_max) * 3 + 2] );
// 			printf("counter: %d\n", counter);
// 		}
// 		else
// 			color += input->all_pts[index * 3 + 2] * 0x000FFFFF;
// 	}
// 	else
// 		color += input->all_pts[index * 3 + 2] * 0x000FFFFF;
// 	color = color | ((unsigned int)0x000000FF);
// 	return (color);
// }

bool	put_point(mlx_image_t *img, int x, int y, unsigned int color)
{
	if (x >= X_IM_SIZE || y >= Y_IM_SIZE || x < 0 || y < 0)
	{
		printf("wrong point!\n");
		return (false);
	}
	mlx_put_pixel(img, x, y, color);
	return (true);
}

double	pyt(int x1, int x2, int y1, int y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

#define WHITE 0xFFFFFFFF
#define BLUE 0x0000FFFF
#define MIN_BLUE 0x00000FFF
#define RED 0xFF0000FF
#define MIN_RED 0x0F0000FF
#define GREEN 0x00FF00FF
#define MIN_GREEN 0x000F00FF

//0xRRGGBBAA
void get_color(t_color *color)
{
	double			dist;
	double			progress;
	double			z_progress;
	uint32_t		cur;
	u_int32_t		col_max;

	color->color = WHITE;
	if (!color->org_z1 && !color->org_z2)
		return ;
	color->color = 0;
	dist = pyt(color->x1, color->x2, color->y1, color->y2);
	progress = pyt(color->x1, color->x_now, color->y1, color->y_now) / dist;
	z_progress = progress * (color->org_z1 - color->org_z2);

	// z <  always blue
	if (z_progress < 0)
	{
		col_max = 0xFF;
		double	current_z = (z_progress / color->min_z + color->org_z1);
		double	strength = current_z / color->max_z;
		((char*)(&(color->color)))[2] = col_max * strength;
		
	}
	//z > 0 always in red and green range
	else
	{
		col_max = 0xFFFF;
	}
	//color->color | 0x000000FF;
}
