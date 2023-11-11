/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:18:01 by frapp             #+#    #+#             */
/*   Updated: 2023/11/10 23:43:24 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	get_max_count(char *path)
{
	int		fd1;
	char	*line;
	size_t	count;
	size_t	x;

	fd1 = open(path, O_RDONLY);
	line = get_next_line(fd1);
	x = 0;
	count = 0;
	while (line && line[x])
	{
		if (ft_isdigit(line[x]))
			count++;
		x++;
	}
	x = count;
	count = 0;
	while (line)
	{
		free(line);
		line = NULL;
		count += x;
		line = get_next_line(fd1);
	}
	return (close(fd1), count * 3);
}

bool	fill_input_hex(t_input *input, char *path)
{
	int		fd1;
	char	*line;
	int		z;
	int		x;
	int		i;
	int		color_index = 0;
	unsigned int temp;

	input->x_max = -1;
	input->y_max = 0;
	input->hex = true;
	input->all_pts = ft_calloc(get_max_count(path), sizeof(int));
	input->colors = ft_calloc(get_max_count(path) / 3, sizeof(unsigned));
	if (!path)
		return (false);
	fd1 = open(path, O_RDONLY);
	line = get_next_line(fd1);
	i =0;
	if (!line)
		return (false);
	z = ft_atoi(line);
	input->z_min = z;
	input->z_max = z;
	i = 0;
	while (line)
	{
		x = 0;
		//ft_printf ("%s", line);
		while (*line && *line != '\n')
		{
			while (ft_iswhitespace(*line) && *line != '\n')
				line++;

			if(*line == '\n' || !(*line))
				break ;
			if (input->y_max == 0)
				(input->x_max)++;
			z = ft_atoi(line);
			//printf("%d ", z);
			z /= input->z_divisor;
			if (z < input->z_min)
				input->z_min = z;
			if (z > input->z_max)
				input->z_max = z;
			input->all_pts[i + 0] = x++;
			input->all_pts[i + 1] = input->y_max;
			input->all_pts[i + 2] = z;
			i += 3;
			while(ft_isdigit(*line))
				line++;
			if (*line == ',')
			{
				line += 3;
				temp = 0;
				while (!ft_iswhitespace(*line) && *line)
				{
					if (*line )
					temp *= 16;
					temp += (unsigned)(*(line++) - '0');
					
					//printf("%c ", *(line-1));
				}
				(input->colors)[color_index++] = temp;
			}
		}
		//printf ("\n");
		(input->y_max)++;
		line = get_next_line(fd1);
	}
	return ((input->y_max)--,close(fd1),true);
}

bool	fill_input(t_input *input, char *path)
{
	int		fd1;
	char	*line;
	int		z;
	int		x;
	int		i;

	input->all_pts = ft_calloc(get_max_count(path), sizeof(int));
	if (!path)
		return (false);
	input->x_max = -1;
	input->y_max = 0;
	
	fd1 = open(path, O_RDONLY);
	line = get_next_line(fd1);
	i =0;
	while (line[i])
	{
		if (line[i++] == 'x')
			return (close(fd1), free(line), fill_input_hex(input, path));
	}
	input->hex = false;
	if (!line)
		return (false);
	z = ft_atoi(line);
	input->z_min = z;
	input->z_max = z;
	i = 0;
	while (line)
	{
		x = 0;
		//ft_printf ("%s", line);
		while (*line && *line != '\n')
		{
			while (ft_iswhitespace(*line) && *line != '\n')
				line++;
			if(*line == '\n' || !(*line))
				break ;
			if (input->y_max == 0)
				(input->x_max)++;
			z = ft_atoi(line);
			z /= input->z_divisor;
			if (z < input->z_min)
				input->z_min = z;
			if (z > input->z_max)
				input->z_max = z;
			input->all_pts[i + 0] = x++;
			input->all_pts[i + 1] = input->y_max;
			input->all_pts[i + 2] = z;
			i += 3;
			while(*line && !ft_iswhitespace(*line))
				line++;
		}
		(input->y_max)++;
		line = get_next_line(fd1);
	}
	return ((input->y_max)--, close(fd1), true);
}

void	handle_key_presses(mlx_key_data_t keydata, void *arg)
{
	if (keydata.key  == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		((t_window *)arg)->elevation_angle += M_PI / 64;
		//if (((t_window *)arg)->elevation_angle > M_PI)
		//	((t_window *)arg)->elevation_angle = M_2_PI;//((t_window *)arg)->elevation_angle - M_PI;
		update_image((t_window *)arg);
		printf("elevation angle: %f\nrotation angle: %f\n",((t_window *)arg)->elevation_angle, ((t_window *)arg)->rotation_angle);
	}
	else if (keydata.key  == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		((t_window *)arg)->rotation_angle -= M_PI / 64;
		//if (((t_window *)arg)->rotation_angle < 0)
		//	((t_window *)arg)->rotation_angle = M_2_PI;// + ((t_window *)arg)->rotation_angle;
		update_image((t_window *)arg);
		printf("elevation angle: %f\nrotation angle: %f\n",((t_window *)arg)->elevation_angle, ((t_window *)arg)->rotation_angle);
	}
	else if (keydata.key  == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		((t_window *)arg)->rotation_angle += M_PI / 64;
	//	if (((t_window *)arg)->rotation_angle > M_PI)
		//	((t_window *)arg)->rotation_angle = M_2_PI;//((t_window *)arg)->rotation_angle - M_PI;
		update_image((t_window *)arg);//
		printf("elevation angle: %f\nrotation angle: %f\n",((t_window *)arg)->elevation_angle, ((t_window *)arg)->rotation_angle);
		
	}
	else if (keydata.key  == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		((t_window *)arg)->elevation_angle -= M_PI / 64;
	//	if (((t_window *)arg)->elevation_angle < 0)
		//	((t_window *)arg)->elevation_angle = M_2_PI;// + ((t_window *)arg)->elevation_angle;
		update_image((t_window *)arg);
		printf("elevation angle: %f\nrotation angle: %f\n",((t_window *)arg)->elevation_angle, ((t_window *)arg)->rotation_angle);
	}
	else if (keydata.key  == MLX_KEY_0 && keydata.action == MLX_PRESS)
	{
		((t_window *)arg)->elevation_angle = M_PI;
		((t_window *)arg)->rotation_angle = M_PI;
		update_image((t_window *)arg);
		printf("elevation angle: %f\nrotation angle: %f\n",((t_window *)arg)->elevation_angle, ((t_window *)arg)->rotation_angle);
	}
	else if (keydata.key  == MLX_KEY_9 && keydata.action == MLX_PRESS)
	{
		((t_window *)arg)->elevation_angle -= M_PI_4;
		update_image((t_window *)arg);
		printf("elevation angle: %f\nrotation angle: %f\n",((t_window *)arg)->elevation_angle, ((t_window *)arg)->rotation_angle);
	}
	else if (keydata.key  == MLX_KEY_8 && keydata.action == MLX_PRESS)
	{
		((t_window *)arg)->rotation_angle -= M_PI_4;
		update_image((t_window *)arg);
		printf("elevation angle: %f\nrotation angle: %f\n",((t_window *)arg)->elevation_angle, ((t_window *)arg)->rotation_angle);
	}
	else if (keydata.key  == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
	{
		if (((t_window *)arg)->points->ptr)
			mlx_delete_image(((t_window *)arg)->mlx, ((t_window *)arg)->points->ptr);
		free(((t_window *)arg)->input->all_pts);
		((t_window *)arg)->input->all_pts = NULL;
		free(((t_window *)arg)->points);
		((t_window *)arg)->points = ft_calloc(1, sizeof(t_img));
		(((t_window *)arg)->input->z_divisor) -= (2.0/8);
		fill_input(((t_window *)arg)->input, ((t_window *)arg)->argv);
		update_image((t_window *)arg);
		printf("z divisor: %f\n", ((t_window *)arg)->input->z_divisor);
	}
	else if (keydata.key  == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
	{
		if (((t_window *)arg)->points->ptr)
			mlx_delete_image(((t_window *)arg)->mlx, ((t_window *)arg)->points->ptr);
		free(((t_window *)arg)->input->all_pts);
		((t_window *)arg)->input->all_pts = NULL;
		free(((t_window *)arg)->points);
		((t_window *)arg)->points = ft_calloc(1, sizeof(t_img));
		(((t_window *)arg)->input->z_divisor) += (2.0/8);
		fill_input(((t_window *)arg)->input, ((t_window *)arg)->argv);
		update_image((t_window *)arg);
		printf("z divisor: %f\n", ((t_window *)arg)->input->z_divisor);
	}
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(arg);
}

//126
//123 124
//125