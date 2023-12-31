/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:24:52 by frapp             #+#    #+#             */
/*   Updated: 2023/12/31 01:10:56 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	check_dimetric(bool dimetric, int *all_pts) {
	if (!dimetric)
		return ;
	while (*all_pts != INT_MIN) {
		*(all_pts + 1) /= DIMETRIC_Y_DIVISOR;
		all_pts += POINT_SIZE;
	}
}

static size_t	count_points_in_file(char *path) {
	int		fd;
	char	*line;
	size_t	count;
	size_t	x;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	x = 0;
	count = 0;
	while (line && line[x]) {
		if (ft_isdigit(line[x]))
			count++;
		x++;
	}
	x = count;
	count = 0;
	while (line) {
		free(line);
		count += x;
		line = get_next_line(fd);
	}
	return (close(fd), count * POINT_SIZE);
}

static void	process_one_line(char *line, t_input *input, int *i) {
	while (*line && *line != '\n') {
		while (*line && ft_iswhitespace(*line) && *line != '\n')
			line++;
		if (*line == '\n' || !(*line))
			return ;
		input->all_pts[*i + X_OFFSET] = (input->x_max)++;
		input->all_pts[*i + Y_OFFSET] = input->y_max;
		input->all_pts[*i + Z_OFFSET] = ft_atoi(line);
		if (input->all_pts[*i + Z_OFFSET] < input->z_min)
			input->z_min = input->all_pts[*i + Z_OFFSET];
		if (input->all_pts[*i + Z_OFFSET] > input->z_max)
			input->z_max = input->all_pts[*i + Z_OFFSET];
		*i += POINT_SIZE;
		while (*line && !ft_iswhitespace(*line))
			line++;
	}
	return ;
}

static bool	process_lines(t_input *input, int fd) {
	char	*line = get_next_line(fd);
	int		i = 0;

	input->all_pts[2] = ft_atoi(line);
	input->z_min = input->all_pts[2];
	input->z_max = input->all_pts[2];
	(input->x_max) = 0;
	while (line) {
		if (*line != '\n')
			(input->x_max) = 0;
		process_one_line(line, input, &i);
		free(line);
		(input->y_max)++;
		line = get_next_line(fd);
	}
	input->all_pts[i] = INT_MIN;
	return (true);
}

static bool	process_file_content(t_input *input, int fd) {
	if (!process_lines(input, fd))
		return (false);
	input->x_max--;
	input->y_max--;
	return (true);
}

bool	parser(t_input *input, char *path, bool dimetric) {
	int	fd;

	input->all_pts = ft_calloc(count_points_in_file(path) + 1, sizeof(int));
	if (!input->all_pts)
		return (false);
	input->y_max = 0;
	fd = open(path, O_RDONLY);
	if (!fd)
		return (false);
	if (fd < 0 || !process_file_content(input, fd)) {
		close(fd);
		return (false);
	}
	close(fd);
	check_dimetric(dimetric, input->all_pts);
	return (true);
}
