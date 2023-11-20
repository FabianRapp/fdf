/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:34:47 by frapp             #+#    #+#             */
/*   Updated: 2023/11/20 11:18:34 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_points(double *x, double *y, t_input *input)
{
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	int		i;
	const double zero = 0.0001;

	min_x = x[0];
	max_x = x[0];
	min_y = y[0];
	max_y = y[0];
	for (int index_y = 0; index_y <= input->y_max; index_y++)
	{
		for (int index_x = 0; index_x <= input->x_max; index_x++)
		{
			i = (input->x_max + 1) * index_y + index_x;
			if (x[i] > max_x)
				max_x = x[i];
			if (x[i] < min_x)
				min_x = x[i];
			if (y[i] > max_y)
				max_y = y[i];
			if (y[i] < min_y)
				min_y = y[i];
		}
	}
	i = 0;
	while (i < (input->x_max + 1) * (input->y_max +1))
	{
		if (fabs(max_x - min_x) < zero)
			max_x += zero;
		x[i] = (X_IM_SIZE * 0.05 + (x[i] - min_x) * ((0.9 * X_IM_SIZE) / (max_x - min_x)));

		if (fabs(max_y - min_y) < zero)
			max_y += zero;
		y[i] = (Y_IM_SIZE * 0.05 + (y[i] - min_y) * ((0.9 * Y_IM_SIZE) / (max_y - min_y)));
		i++;
	}

}


void update_image(t_window *window)
{
	if (window->points->ptr)
		mlx_delete_image(window->mlx, window->points->ptr);
	window->points->ptr = NULL;
	window->points->ptr = mlx_new_image(window->mlx, X_IM_SIZE, Y_IM_SIZE);
	ft_memset(window->points->ptr->pixels, 0, X_IM_SIZE * Y_IM_SIZE * sizeof(int32_t));
	mlx_image_to_window(window->mlx, window->points->ptr, 0, 0);
	calulate_isometric_coordinates(window->input, &(window->points->xi), &(window->points->yi), window->elevation_angle, window->rotation_angle, window);
	draw(window, window->input, window->points->xi, window->points->yi);
	free(window->points->xi);
	free(window->points->yi);
}


// #define TOLERANCE 1e-9 // Tolerance level can be adjusted based on the precision you need.

// bool isNotMultipleOfPi(double value) {
// 	// Normalize value by modulo with 2*PI to get value in the range [0, 2*PI)
// 	value = fmod(value, 2 * M_PI);

// 	// Check if the value is within the tolerance of any multiple of PI.
// 	double remainder = fmod(value, M_PI);

// 	if (remainder < TOLERANCE || (M_PI - remainder) < TOLERANCE) {
// 		// The value is too close to being a multiple of PI.
// 		return false;
// 	}

// 	// The value is not a multiple of PI within the defined tolerance.
// 	return true;
// }

// caller handles malloc error and free
// angles in M_PI

// The x coordinate is the rotated x value
// The y coordinate is a combination of the rotated y and the z value,
void	calulate_isometric_coordinates(t_input *input, int **xi, int **yi, double elevation_angle, double rotation_angle, t_window *window)
{
	double	*x;
	double	*y;
	int		i;
	int		x_val;
	int		y_val;
	int		z_val;
	double	rotatedy;
	double	rotatedx;

	x = calloc(((input->x_max + 1) * (input->y_max + 1) + 1), sizeof(double));
	y = calloc(((input->x_max + 1) * (input->y_max + 1) + 1), sizeof(double));
	*xi = calloc(((input->x_max + 1) * (input->y_max + 1) + 1), sizeof(int));
	*yi = calloc(((input->x_max + 1) * (input->y_max + 1) + 1), sizeof(int));
	if (!x || !y)
		return ;

	double cos_angle = cos(rotation_angle);
	double sin_angle = sin(rotation_angle);
	double cos_elev = cos(elevation_angle);
	double sin_elev = sin(elevation_angle);
	i = 0;
	int i2 = 0;
	while (i2 <= input->y_max * (input->x_max + 1) + input->x_max)
	{
	//for (int index_y = 0; index_y <= input->y_max; index_y++) {
		//for (int index_x = 0; index_x <= input->x_max; index_x++) {
			//int i = (index_y * (input->x_max + 1) + index_x) * 3;
			int i = i2 * 3;
			double x_val = (double)(input->all_pts[i]);
			double y_val = (double)(input->all_pts[i + 1]);
			//x[index_y * (input->x_max + 1) + index_x] = x_val + (x_val * cos_angle - y_val * sin_angle);
			//y[index_y * (input->x_max + 1) + index_x] = y_val + (x_val * sin_elev + y_val * cos_elev) * cos_elev - (double)(input->all_pts[i + 2]) * sin_elev;
			x[i2] = x_val + (x_val * cos_angle - y_val * sin_angle);
			y[i2] = y_val + (x_val * sin_elev + y_val * cos_elev) * cos_elev - (double)(input->all_pts[i + 2]) * sin_elev;
		//}
		i2++;
	}
	scale_points(x, y, input);
	i = -1;
	while (++i < (input->x_max + 1) * (input->y_max + 1))
	{
		(*xi)[i] = (int)(x[i]);
		(*yi)[i] = (int)(y[i]);
	}
	free(x);
	free(y);
}

int main(int ac, char *av[])
{
	t_window	window;
	t_input		input;
	t_img		*pts;

	window.argv = av[1];
	window.input= &input;
	init_window(&window);
	window.points = ft_calloc(1, sizeof(t_img));
	//window.points = malloc(sizeof(t_img));
	pts = window.points;
	pts->ptr = NULL;
	input.z_divisor = 1;
	fill_input(&input, av[1]);
	window.elevation_angle = M_PI_4;
	window.rotation_angle = M_PI_4;
	update_image(&window);// window.points->xi, window.points->yi);
	for (int i = 0; i < (input.x_max + 1) * (input.y_max +1); i++)
	{
		// printf("x: %d, y: %d, z: %d\n", input.all_pts[i*3], input.all_pts[i*3 + 1], input.all_pts[i*3 + 2]);
		// if (input.hex)
		// {
		// 	if (!input.colors[i])
		// 		printf("no col\n");
		// 	else
		// 		printf("col: %08X\n", ((unsigned int *)(input.colors))[i]);
		// }
	}
	mlx_key_hook(window.mlx, &handle_key_presses, (void *)(&window));
	mlx_loop(window.mlx);
	clean_exit(&window);
	return (0);
}

	//cc main.c input.c utils1.c libft.a -framework Cocoa -framework OpenGL -framework IOKit libmlx42.a -Iinclude -lglfw -L"/Users/frapp/.brew/opt/glfw/lib/"

	//cc -g -o ../../debugger/a.out cc main.c input.c utils1.c libft.a -framework Cocoa -framework OpenGL -framework IOKit libmlx42.a -Iinclude -lglfw -L"/Users/frapp/.brew/opt/glfw/lib/"

	// /Users/frapp/.vscode/extensions/vadimcn.vscode-lldb-1.10.0/adapter/codelldb terminal-agent --connect=49303

	// cc -g -o ../../debugger/a.out main.c input.c utils1.c minilibx_macos/libmlx.a libft.a -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
	
	
	//cc -g -o ../../debugger/a.out main.c input.c utils1.c libft.a -framework Cocoa -framework OpenGL -framework IOKit libmlx42.a -Iinclude -lglfw -L"/Users/frapp/.brew/opt/glfw/lib/"
