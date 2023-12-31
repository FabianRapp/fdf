/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 20:44:17 by frapp             #+#    #+#             */
/*   Updated: 2023/12/31 01:05:47 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	set_background_color2(char *color_str, u_int32_t *color)
{
	if (color_str && !ft_strcmp(color_str, "white"))
		*color = 0xFFFFFFFF;
	else if (color_str && !ft_strcmp(color_str, "red"))
		*color = 0xFF0000FF;
	if (color_str && !ft_strcmp(color_str, "green"))
		*color = 0xFF00FF00;
	else if (color_str && !ft_strcmp(color_str, "blue"))
		*color = 0xFFFF0000;
	else if (color_str && !ft_strcmp(color_str, "yellow"))
		*color = 0xFF00FFFF;
	else if (color_str && !ft_strcmp(color_str, "cyan"))
		*color = 0xFFFFFF00;
	else if (color_str && !ft_strcmp(color_str, "magenta"))
		*color = 0xFFFF00FF;
	else if (color_str && !ft_strcmp(color_str, "orange"))
		*color = 0xFF00A5FF;
	else if (color_str && !ft_strcmp(color_str, "lime"))
		*color = 0xFF00FF00;
	else
		return (false);
	return (true);
}

void	set_background_color(char *color_str,
	uint32_t *pixels, uint16_t alpha)
{
	int			i;
	uint32_t	color;

	if (!set_background_color2(color_str, &color))
		color = 0xFF000000;
	if (alpha)
		((u_int8_t *)(&color))[3] = alpha;
	i = 0;
	while (i <= X_IM_SIZE * Y_IM_SIZE)
	{
		pixels[i] = color;
		i++;
	}
}

bool give_input_feedback(void)
{
	ft_printf("1.) Argument:\n\tMust be the path to the data\n");
	ft_printf("2.) Argument(optional, \"-999\" to make this argument invalid):\n\tinteger value for the lowest z value\n");
	ft_printf("3.) Argument(optional):\n\t\"dimetric\" to use adimetric projection\n");
	ft_printf("4.) Argument(optional):\n\tBackground color: \"white\", \"red\", \"green\", \"blue\", \"yellow\" \"cyan\", \"magenta\", \"orange\", \"lime\"\n");
	ft_printf("5.) Argument (optional):\n\tThe opacity of the background color (1 to 255)\n");

	return false;
}

void print_controls(void)
{
	ft_printf("Keybinds:\n");
	ft_printf("\tUP/DOWN: Tilt object\n");
	ft_printf("\tLEFT/RIGHT: Rotate object\n");
	ft_printf("\tNUM_PLUS/NUM_MINUS: Zoom\n");
	ft_printf("\tQ/W: Move object on x-Axis\n");
	ft_printf("\tA/S: Move object on y-Axis\n");
	ft_printf("\tZ/X: Move object on z-Axis\n");
}
