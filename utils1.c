/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:19:53 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 21:40:48 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	clean_exit(t_window *window)
{
	mlx_delete_image(window->mlx, window->img.ptr);
	mlx_terminate(window->mlx);
	free(window->input.all_pts);
	if (window->img.xi)
		free(window->img.xi);
	if (window->img.yi)
		free(window->img.yi);
	exit(0);
	return (0);
}

mlx_t	*init_window(t_window *window)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	window->mlx = mlx_init(X_SIZE, Y_SIZE, "fdf", true);
	return (window->mlx);
}

bool	free_arrays(double *a, double *b, int *c, int *d)
{
	if (a && b && c && d)
		return (true);
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
	return (false);
}
