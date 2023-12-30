/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:24:52 by frapp             #+#    #+#             */
/*   Updated: 2023/12/30 23:41:09 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_max_count(char *path)
{
	int		fd;
	char	*line;
	size_t	count;
	size_t	x;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
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
		line = get_next_line(fd);
	}
	return (close(fd), count * 3);
}

bool	initialize_processing(t_input *input, int fd, char **line, int *i)
{
	*i = 0;
	*line = get_next_line(fd);
	if (!*line)
		return (false);
	input->all_pts[*i + 2] = ft_atoi(*line);
	input->z_min = input->all_pts[*i + 2];
	input->z_max = input->all_pts[*i + 2];
	return (true);
}

static char	*loop(char *line, t_input *input, int *i)
{
	while (*line && *line != '\n')
	{
		while (*line && ft_iswhitespace(*line) && *line != '\n')
			line++;
		if (*line == '\n' || !(*line))
			break ;
		input->all_pts[*i + 0] = (input->x_max)++;
		input->all_pts[*i + 1] = input->y_max;
		input->all_pts[*i + 2] = ft_atoi(line);
		if (input->all_pts[*i + 2] < input->z_min)
			input->z_min = input->all_pts[*i + 2];
		if (input->all_pts[*i + 2] > input->z_max)
			input->z_max = input->all_pts[*i + 2];
		*i += 3;
		while (*line && !ft_iswhitespace(*line))
			line++;
	}
	return (line);
}

bool	process_lines(t_input *input, int fd, char *line, int i)
{
	char	*base_line;

	base_line = line;
	while (line)
	{
		if (*line && *line != '\n')
			(input->x_max) = 0;
		line = loop(line, input, &i);
		(input->y_max)++;
		line = get_next_line(fd);
		if (base_line)
			free(base_line);
		base_line = line;
	}
	input->all_pts[i] = INT_MIN;
	return (true);
}
