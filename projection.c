/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:08:25 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 21:40:06 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_scaling(double *x, double *y, struct s_scaling_data *data,
	t_input *input)
{
	data->x_min = x[0];
	data->x_max = x[0];
	data->y_min = y[0];
	data->y_max = y[0];
	data->i = 0;
	while (data->i < (input->x_max + 1) * (input->y_max +1))
	{
		if (x[data->i] < data->x_min)
			data->x_min = x[data->i];
		if (x[data->i] > data->x_max)
			data->x_max = x[data->i];
		if (y[data->i] < data->y_min)
			data->y_min = y[data->i];
		if (y[data->i] > data->y_max)
			data->y_max = y[data->i];
		data->i++;
	}
	data->x_range = data->x_max - data->x_min;
	data->y_range = data->y_max - data->y_min;
}

// input->translation_vector[0,1,2] 3D chords
// input->translation_vector[3,4] isometric chords
void	get_translation_vector(t_input *input, t_window *window,
	struct s_scaling_data *data)
{
	struct s_isometric_calc	calc;

	calc.cos_angle = cos(window->rotation_angle);
	calc.sin_angle = sin(window->rotation_angle);
	calc.cos_elev = cos(window->elevation_angle);
	calc.sin_elev = sin(window->elevation_angle);
	input->translation_vector[3] = input->translation_vector[0] * calc.cos_angle
		- input->translation_vector[1] * calc.sin_angle;
	input->translation_vector[4] = input->translation_vector[0] * calc.sin_elev
		* calc.sin_angle + input->translation_vector[1] * calc.sin_elev
		* calc.cos_angle - input->translation_vector[2] * calc.cos_elev;
	data->x_offset = input->translation_vector[3]
		* data->scale_factor + data->x_offset;
	data->y_offset = input->translation_vector[4]
		* data->scale_factor + data->y_offset;
}

void	scale_points(double *x, double *y, t_input *input, t_window *window)
{
	struct s_scaling_data	data;

	init_scaling(x, y, &data, input);
	data.x_scale = X_IM_SIZE / data.x_range;
	data.y_scale = Y_IM_SIZE / data.y_range;
	if (data.x_scale < data.y_scale)
		data.scale_factor = data.x_scale * input->zoom;
	else
		data.scale_factor = data.y_scale * input->zoom;
	data.x_center = X_IM_SIZE / 2;
	data.y_center = Y_IM_SIZE / 2;
	data.x_offset = (X_IM_SIZE - (data.x_range * data.scale_factor))
		/ 2 - data.x_min * data.scale_factor;
	data.y_offset = (Y_IM_SIZE - (data.y_range * data.scale_factor))
		/ 2 - data.y_min * data.scale_factor;
	get_translation_vector(input, window, &data);
	data.i = 0;
	while (data.i < (input->x_max + 1) * (input->y_max +1))
	{
		x[data.i] = x[data.i] * data.scale_factor + data.x_offset;
		y[data.i] = y[data.i] * data.scale_factor + data.y_offset;
		data.i++;
	}
}

bool	init_calc(struct s_isometric_calc *calc, int **xi,
	int **yi, t_window *window)
{
	calc->x = calloc(((window->input.x_max + 1)
				* (window->input.y_max + 1) + 1), sizeof(double));
	calc->y = calloc(((window->input.x_max + 1)
				* (window->input.y_max + 1) + 1), sizeof(double));
	*xi = calloc(((window->input.x_max + 1)
				* (window->input.y_max + 1) + 1), sizeof(int));
	*yi = calloc(((window->input.x_max + 1)
				* (window->input.y_max + 1) + 1), sizeof(int));
	if (!free_arrays(calc->x, calc->y, *xi, *yi))
		return (clean_exit(window));
	calc->cos_angle = cos(window->rotation_angle);
	calc->sin_angle = sin(window->rotation_angle);
	calc->cos_elev = cos(window->elevation_angle);
	calc->sin_elev = sin(window->elevation_angle);
	calc->i = 0;
	while (calc->i <= window->input.y_max * (window->input.x_max + 1)
		+ window->input.x_max && window->dimetric)
		window->input.all_pts[(calc->i++) * 3 + 1] /= 2;
	calc->i = 0;
	window->dimetric = false;
	return (true);
}

int	calulate_isometric_coordinates(t_input *input,
	int **xi, int **yi, t_window *window)
{
	struct s_isometric_calc	calc;

	if (!init_calc(&calc, xi, yi, window))
		return (0);
	while (calc.i <= input->y_max * (input->x_max + 1) + input->x_max)
	{
		calc.x[calc.i] = input->all_pts[(calc.i * 3)] * calc.cos_angle
			- input->all_pts[(calc.i * 3) + 1] * calc.sin_angle;
		calc.y[calc.i] = input->all_pts[(calc.i * 3)] * calc.sin_elev
			* calc.sin_angle + input->all_pts[(calc.i * 3) + 1] * calc.sin_elev
			* calc.cos_angle - input->all_pts[(calc.i * 3) + 2] * calc.cos_elev;
		calc.i++;
	}
	scale_points(calc.x, calc.y, input, window);
	calc.i = 0;
	while (calc.i < (input->x_max + 1) * (input->y_max + 1))
	{
		(*xi)[calc.i] = (int)round(calc.x[calc.i]);
		(*yi)[calc.i] = (int)round(calc.y[calc.i]);
		calc.i++;
	}
	free(calc.x);
	free(calc.y);
	return (1);
}
