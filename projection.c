/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:08:25 by frapp             #+#    #+#             */
/*   Updated: 2023/12/31 01:17:55 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

bool	init_calc(struct s_isometric_calc *calc, int **prj_x,
	int **prj_y, t_window *window)
{
	calc->count = (window->input.x_max + 1) * (window->input.y_max + 1);
	calc->x = calloc(calc->count + 1, sizeof(double));
	calc->y = calloc(calc->count + 1, sizeof(double));
	*prj_x = calloc(calc->count + 1, sizeof(int));
	*prj_y = calloc(calc->count + 1, sizeof(int));
	if (!free_on_fail(&(calc->x), &(calc->y), prj_x, prj_y))
		return (clean_exit(window));
	calc->cos_angle = cos(window->rotation_angle);
	calc->sin_angle = sin(window->rotation_angle);
	calc->cos_elev = cos(window->elevation_angle);
	calc->sin_elev = sin(window->elevation_angle);
	return (true);
}

int	calulate_isometric_coordinates(t_input *input,
	int **prj_x, int **prj_y, t_window *window)
{
	struct s_isometric_calc	calc;
	int						point_index;

	if (!init_calc(&calc, prj_x, prj_y, window))
		return (0);
	for (int i = 0; i < calc.count; i++)
	{
		point_index = i * POINT_SIZE;
		calc.x[i] = input->all_pts[point_index + X_OFFSET] * calc.cos_angle
			- input->all_pts[point_index + Y_OFFSET] * calc.sin_angle;
		calc.y[i] = input->all_pts[point_index + X_OFFSET] * calc.sin_elev
			* calc.sin_angle + input->all_pts[point_index + Y_OFFSET] * calc.sin_elev
			* calc.cos_angle - input->all_pts[point_index + Z_OFFSET] * calc.cos_elev;
	}
	scale_points(calc.x, calc.y, input, window);
	for (int i = 0; i < calc.count; i++)
	{
		(*prj_x)[i] = (int)round(calc.x[i]);
		(*prj_y)[i] = (int)round(calc.y[i]);
	}
	free(calc.x);
	free(calc.y);
	return (1);
}
