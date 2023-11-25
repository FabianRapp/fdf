/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:18:01 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 15:51:35 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	process_file_content(t_input *input, int fd)
{
	char	*line;
	int		i;

	if (!initialize_processing(input, fd, &line, &i))
		return (false);
	return (process_lines(input, fd, line, i));
}

bool	fill_input(t_input *input, char *path)
{
	int	fd;

	input->zoom = 1;
	input->all_pts = ft_calloc(get_max_count(path), sizeof(int));
	if (!input->all_pts)
		return (false);
	input->y_max = 0;
	fd = open(path, O_RDONLY);
	if (!fd)
		return (false);
	if (fd < 0 || !process_file_content(input, fd))
	{
		close(fd);
		return (false);
	}
	(input->x_max)--;
	(input->y_max)--;
	close(fd);
	return (true);
}

bool	handle_key_presses2(mlx_key_data_t keydata, void *arg)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		((t_window *)arg)->input.translation_vector[0] += 2;
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		((t_window *)arg)->input.translation_vector[0] -= 2;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		((t_window *)arg)->input.translation_vector[1] += 2;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		((t_window *)arg)->input.translation_vector[1] -= 2;
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		((t_window *)arg)->input.translation_vector[2] += 2;
	else if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		((t_window *)arg)->input.translation_vector[2] -= 2;
	else
		return (false);
	return (true);
}

void	handle_key_presses(mlx_key_data_t keydata, void *arg)
{
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		((t_window *)arg)->elevation_angle += M_PI / 64;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		((t_window *)arg)->rotation_angle -= M_PI / 64;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		((t_window *)arg)->rotation_angle += M_PI / 64;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		((t_window *)arg)->elevation_angle -= M_PI / 64;
	else if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		(((t_window *)arg)->input.zoom) *= 1.05;
	else if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
		(((t_window *)arg)->input.zoom) *= 0.95;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(arg);
	else if (handle_key_presses2(keydata, arg))
		return (update_image((t_window *)arg));
	else
		return ;
	update_image((t_window *)arg);
}
