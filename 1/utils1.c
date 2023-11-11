/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:19:53 by frapp             #+#    #+#             */
/*   Updated: 2023/11/10 23:00:31 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	clean_exit(t_window *window)
{
	mlx_delete_image(window->mlx, window->points->ptr);
	free(window->points);
	free(window->input->all_pts);
	if (window->input->hex)
		free(window->input->colors);
	exit(0);
	return (0);
}

void	init_window(t_window *window)
{
	t_img		*cur_img;

	mlx_set_setting(MLX_MAXIMIZED, false);
	window->mlx = mlx_init(X_SIZE, Y_SIZE, "fdf", true);
}

	//window->w_ptr = mlx_new_window(window->mlx, window->w_sizes[0], window->w_sizes[1], "fdf");
	// mlx_key_hook(window->mlx, &handle_key_presses, NULL);
	//mlx_hook(window->w_ptr, 17, 1L << 17, clean_exit, &window);
