/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rgba.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:13:11 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 19:53:23 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	progress_minus1(t_color *color)
{
	color->rgba1.start_red = 0x0d;
	color->rgba1.start_green = 0x98;
	color->rgba1.start_blue = 0xba;
	color->rgba1.end_red = 0;
	color->rgba1.end_green = 0;
	color->rgba1.end_blue = 0xFF;
}

void	progress_minus2(t_color *color)
{
	color->rgba2.start_red = 0xFF;
	color->rgba2.start_green = 0xFF;
	color->rgba2.start_blue = 0xFF;
	color->rgba2.end_red = 0x0d;
	color->rgba2.end_green = 0x98;
	color->rgba2.end_blue = 0xba;
}

void	progress_pos1(t_color *color)
{
	color->rgba3.start_red = 128;
	color->rgba3.start_green = 0;
	color->rgba3.start_blue = 128;
	color->rgba3.end_red = 0xFF;
	color->rgba3.end_green = 190;
	color->rgba3.end_blue = 100;
}

void	progress_pos2(t_color *color)
{
	color->rgba4.start_red = 0xFF;
	color->rgba4.start_green = 0xFF;
	color->rgba4.start_blue = 0xFF;
	color->rgba4.end_red = 128;
	color->rgba4.end_green = 0;
	color->rgba4.end_blue = 128;
}

// void	progress_pos2(t_color *color)
// {
// 	color->rgba4.start_red = 0xFF;
// 	color->rgba4.start_green = 0xFF;
// 	color->rgba4.start_blue = 0xFF;
// 	color->rgba4.end_red = 128;
// 	color->rgba4.end_green = 0;
// 	color->rgba4.end_blue = 128;
// }

void	init_rgba(t_color *color)
{
	progress_minus1(color);
	progress_minus2(color);
	progress_pos1(color);
	progress_pos2(color);
}
