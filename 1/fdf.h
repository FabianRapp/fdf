/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:29:17 by frapp             #+#    #+#             */
/*   Updated: 2023/11/11 02:43:08 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#ifndef X_SIZE
# define X_SIZE 1400
#endif

#ifndef Y_SIZE
# define Y_SIZE 1400
#endif

#ifndef X_IM_SIZE
# define X_IM_SIZE 1400
#endif

#ifndef Y_IM_SIZE
# define Y_IM_SIZE 1400
#endif

#define COLOR_BASE 0xFFFFFFFF // White color with full alpha
#define COLOR_MIN_SUM 0x28 // The minimum sum of R, G, and B

#include <stdlib.h>
//#include <MLX42/MLX42.h>
#include "MLX42/include/MLX42/MLX42.h"
//#include "MLX42/include/MLX42/MLX42_Int.h"
#include "libft/libft.h"
#include <math.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

typedef struct s_color
{
	int			org_z1;
	int			org_z2;
	int			max_z;
	int			min_z;
	int			y1;
	int			y2;
	int			x1;
	int			x2;
	int			x_now;
	int			y_now;
	uint32_t	color;
} t_color;


typedef struct s_line
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	double			l1;
	double			l2;
	int				direct_x;
	int				direct_y;
	bool			get_col;
	t_color			color;
	mlx_image_t		*img;
} t_line;


typedef struct s_input
{
	int	x_max;
	int	y_max;
	int	z_min;
	int	z_max;
	int *all_pts;
	float	z_divisor;
	bool	hex;
	unsigned int	*colors;
} t_input;

typedef struct s_img
{
	mlx_image_t	*ptr;
	int	*xi;
	int	*yi;
	int	count_pts;
}	t_img;

typedef struct s_window
{
	mlx_t	*mlx;
	t_img	*points;
	t_input	*input;
	double		elevation_angle;
	double		rotation_angle;
	char	*argv;
}	t_window;

// main.c
void	update_image(t_window *window);//, int *xi, int *yi);
void	calulate_isometric_coordinates(t_input *input, int **xi, int **yi, double elevation_angle, double rotation_angle, t_window *window);

// input.c
bool	fill_input(t_input *input, char *path);
void	handle_key_presses(mlx_key_data_t keydata, void *arg);
// is static: 
// size_t	get_max_count(char *path);

// utils1.c
int				clean_exit(t_window *window);
void			init_window(t_window *window);

// utils_draw.c
void	get_color(t_color *color);
bool	put_point(mlx_image_t *img, int x, int y, unsigned int color);
void	draw_straight_line(t_line *struc);
void	connect_points(t_line *struc);
#endif