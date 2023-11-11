/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:13:20 by frapp             #+#    #+#             */
/*   Updated: 2023/11/04 01:41:24 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGING_H
# define DEBUGGING_H

#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

# define FOR_LOOP for (int i = 0; i < (input->x_max + 1) * (input->y_max +1); i++)

// fd exists when this is called
// char_str is "x", "y" or "z" and val is an int
# define LOG_ENTRY(char_str, val, index) do {\
	char	*str; \
	if (index > -1) \
	{ \
		write(fd, "index ", 6); \
		str = ft_itoa(index); \
		write(fd, str, ft_strlen(str)); \
		free(str); \
		write(fd, ", ", 2); \
	} \
	str = ft_strjoin(char_str, ": "); \
	write(fd, str, ft_strlen(str)); \
	free(str); \
	str = ft_itoa(val); \
	write(fd, str, ft_strlen(str)); \
	free(str); \
	write(fd, "\n", 1); \
} while (0)

// fd exists when this is called
// char_str is "x", "y" or "z" and val is a flaot or doubble
# define LOG_ENTRY_FLOAT(char_str, val, index) do {\
	char	*str; \
	if (index > -1) \
	{ \
		write(fd, "index ", 6); \
		str = ft_itoa(index); \
		write(fd, str, ft_strlen(str)); \
		free(str); \
		write(fd, ", ", 2); \
	} \
	char	buffer[50]; \
	str = ft_strjoin(char_str, ": "); \
	write(fd, str, ft_strlen(str)); \
	free(str); \
	int len = sprintf(buffer, "%.8f", val); \
	write(fd, buffer, len); \
	write(fd, "\n", 1); \
} while (0)

// Define the CHECK_DIR_EXISTS_OR_CREATE macro
# define CHECK_DIR_EXISTS_OR_CREATE(dir) do { \
	struct stat st = {0}; \
	if (stat(dir, &st) == -1) { \
		if (mkdir(dir, 0755) != 0 && errno != EEXIST) { \
			perror("Error creating directory"); \
			exit(EXIT_FAILURE); \
		} \
	} \
} while(0)

// // utils
// void	scale_points_debug(int *x, int *y, t_input *input);
// void	calulate_isometric_coordinates_debug(t_input *input, int **xi, int **yi, double elevation_angle, double rotation_angle);
// bool	fill_input_debug(t_input *input, char *path);
// size_t	get_max_count_debug(char *path, int fd);

// // utils 2
// void	draw_debug(t_window *window, t_input *input, int *xi, int *yi);
// void	connect_points_debug(int x1, int x2, int y1, int y2, mlx_image_t *img, unsigned int color, int fd);
// void draw_straight_line_debug(int x1, int x2, int y1, int y2, mlx_image_t *img, unsigned int color);


// utils
void	scale_points_debug(double *x, double *y, t_input *input);
void	calulate_isometric_coordinates_debug(t_input *input, int **xi, int **yi, double elevation_angle, double rotation_angle);
bool	fill_input_debug(t_input *input, char *path);
size_t	get_max_count_debug(char *path);

// utils 2
void	draw_debug(t_window *window, t_input *input, int *xi, int *yi);
void	connect_points_debug(int x1, int x2, int y1, int y2, mlx_image_t *img, unsigned int color);
void draw_straight_line_debug(int x1, int x2, int y1, int y2, mlx_image_t *img, unsigned int color);


#endif
