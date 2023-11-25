/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:34:47 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 21:40:38 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_image(t_window *window)
{
	if (window->img.ptr)
		mlx_delete_image(window->mlx, window->img.ptr);
	window->img.ptr = NULL;
	window->img.ptr = mlx_new_image(window->mlx, X_IM_SIZE, Y_IM_SIZE);
	set_background_color(window->color_str,
		(u_int32_t *)(window->img.ptr->pixels), window->alpha);
	mlx_image_to_window(window->mlx, window->img.ptr, 0, 0);
	if (!calulate_isometric_coordinates(&window->input, &(window->img.xi),
			&(window->img.yi), window))
		clean_exit (window);
	draw(window, &(window->input), window->img.xi, window->img.yi);
	free(window->img.xi);
	free(window->img.yi);
	window->img.xi = NULL;
	window->img.yi = NULL;
}

bool	check_file_ending(char *path, t_window *window)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (false);
	if (path[len - 1] != 'f' || path[len - 2]
		!= 'd' || path[len - 3] != 'f'
		|| path[len - 4] != '.')
		return (give_input_feedback());
	window->dimetric = false;
	window->min_displayed_z = INT_MIN;
	window->path = path;
	return (true);
}

bool	init_main(int *ac, char *av[], t_window *window)
{
	window->input.translation_vector[0] = 0;
	window->input.translation_vector[1] = 0;
	window->input.translation_vector[2] = 0;
	window->init = true;
	if (*ac < 2 || *ac > 6)
		return (give_input_feedback());
	if (!check_file_ending(av[1], window))
		return (false);
	if (*ac >= 3 && ft_strcmp("-999", av[2]))
		window->min_displayed_z = ft_atoi(av[2]);
	if (*ac >= 4 && !ft_strcmp("dimetric", av[3]))
		window->dimetric = true;
	window->color_str = NULL;
	if (*ac >= 5)
		window->color_str = av[4];
	window->alpha = 0;
	if (*ac >= 6)
		window->alpha = ft_atoi(av[5]);
	if (!init_window(window))
		return (false);
	window->elevation_angle = 1.521710;
	window->rotation_angle = 0.834485;
	return (true);
}

int	main(int ac, char *av[])
{
	t_window	window;
	t_img		*pts;

	if (!init_main(&ac, av, &window))
		return (0);
	pts = &window.img;
	pts->ptr = NULL;
	if (!fill_input(&window.input, av[1]))
	{
		mlx_terminate(window.mlx);
		return (0);
	}
	print_controls();
	update_image(&window);
	mlx_key_hook(window.mlx, &handle_key_presses, (void *)(&window));
	mlx_loop(window.mlx);
	clean_exit(&window);
	return (0);
}

