/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:29:36 by frapp             #+#    #+#             */
/*   Updated: 2023/11/20 12:55:24 by frapp            ###   ########.fr       */
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


