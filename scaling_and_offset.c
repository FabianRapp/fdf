/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling_and_offset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:12:05 by fabi              #+#    #+#             */
/*   Updated: 2023/12/30 23:41:28 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	init_scaling(double *x, double *y, struct s_scaling_data *data,
	t_input *input)
{
	data->x_min = x[0];
	data->x_max = x[0];
	data->y_min = y[0];
	data->y_max = y[0];
	data->count = (input->x_max + 1) * (input->y_max + 1);
	for (int i = 0; i < data->count; i++)
	{
		if (x[i] < data->x_min)
			data->x_min = x[i];
		if (x[i] > data->x_max)
			data->x_max = x[i];
		if (y[i] < data->y_min)
			data->y_min = y[i];
		if (y[i] > data->y_max)
			data->y_max = y[i];
	}
	data->x_range = data->x_max - data->x_min;
	data->y_range = data->y_max - data->y_min;
	data->x_center = X_IM_SIZE / 2;
	data->y_center = Y_IM_SIZE / 2;
}

static void	calc_offsets(struct s_scaling_data *data, t_input *input)
{
	data->x_scale = X_IM_SIZE / data->x_range;
	data->y_scale = Y_IM_SIZE / data->y_range;
	if (data->x_scale < data->y_scale)
		data->scale_factor = data->x_scale * input->zoom;
	else
		data->scale_factor = data->y_scale * input->zoom;

	data->x_offset = (X_IM_SIZE - (data->x_range * data->scale_factor))
		/ 2 - data->x_min * data->scale_factor;
	data->x_offset = data->translation_x_off
		* data->scale_factor + data->x_offset;
	data->y_offset = (Y_IM_SIZE - (data->y_range * data->scale_factor))
		/ 2 - data->y_min * data->scale_factor;
	data->y_offset = data->translation_y_off
		* data->scale_factor + data->y_offset;
}

static void	apply_offset(double *x, double *y, struct s_scaling_data *data)
{
	for (int i = 0; i < data->count; i++)
	{
		x[i] = x[i] * data->scale_factor + data->x_offset;
		y[i] = y[i] * data->scale_factor + data->y_offset;
	}
}

static void	apply_transvec_projected(t_input *input, t_window *window,
	struct s_scaling_data *data)
{
	double	cos_angle = cos(window->rotation_angle);
	double	sin_angle = sin(window->rotation_angle);
	double	cos_elev = cos(window->elevation_angle);
	double	sin_elev = sin(window->elevation_angle);

	data->translation_x_off = input->translation_vector[0] * cos_angle
		- input->translation_vector[1] * sin_angle;
	data->translation_y_off = input->translation_vector[0] * sin_elev
		* sin_angle + input->translation_vector[1] * sin_elev
		* cos_angle - input->translation_vector[2] * cos_elev;
}

void	scale_points(double *x, double *y, t_input *input, t_window *window)
{
	struct s_scaling_data	data;

	init_scaling(x, y, &data, input);
	apply_transvec_projected(input, window, &data);
	calc_offsets(&data, input);
	apply_offset(x, y, &data);
}
