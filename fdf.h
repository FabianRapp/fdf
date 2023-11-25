/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frapp <frapp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:29:17 by frapp             #+#    #+#             */
/*   Updated: 2023/11/25 21:32:34 by frapp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef X_SIZE
#  define X_SIZE 1400
# endif

# ifndef Y_SIZE
#  define Y_SIZE 1400
# endif

# ifndef X_IM_SIZE
#  define X_IM_SIZE 1400
# endif

# ifndef Y_IM_SIZE
#  define Y_IM_SIZE 1400
# endif

// min 1, lower is better qulity but more cost
# ifndef GRAFIC_LVL
#  define GRAFIC_LVL 1
# endif

# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_input	t_input;

struct s_rgba
{
	uint8_t	start_red;
	uint8_t	start_green;
	uint8_t	start_blue;
	uint8_t	end_red;
	uint8_t	end_green;
	uint8_t	end_blue;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
} ;

typedef struct s_color
{
	int				z_target;
	int				last_z_target;
	int				max_z;
	int				min_z;
	int				y_target;
	int				x_target;
	int				x_now;
	int				y_now;
	int				x_start;
	int				y_start;
	int				min_displayed_z;
	float			z_now;
	uint32_t		color;
	struct s_rgba	*rgba;
	struct s_rgba	rgba1;
	struct s_rgba	rgba2;
	struct s_rgba	rgba3;
	struct s_rgba	rgba4;
}	t_color;

typedef struct s_line
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				l1;
	int				l2;
	int				index;
	int				direct_x;
	int				direct_y;
	bool			get_col;
	t_color			color;
	mlx_image_t		*img;
}	t_line;

struct	s_isometric_calc
{
	double	*x;
	double	*y;
	int		i;
	double	cos_angle;
	double	sin_angle;
	double	cos_elev;
	double	sin_elev;
} ;

typedef struct s_input
{
	int				x_max;
	int				y_max;
	int				z_min;
	int				z_max;
	int				*all_pts;
	float			zoom;
	int				translation_vector[5];
}	t_input;

struct	s_scaling_data
{
	int		i;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	scale_factor;
	double	x_range;
	double	y_range;
	double	x_scale;
	double	y_scale;
	double	x_center;
	double	y_center;
	double	x_offset;
	double	y_offset;
} ;

typedef struct s_img
{
	mlx_image_t	*ptr;
	int			*xi;
	int			*yi;
	int			count_pts;
}	t_img;

typedef struct s_window
{
	mlx_t		*mlx;
	t_img		img;
	t_input		input;
	double		elevation_angle;
	double		rotation_angle;
	char		*path;
	bool		dimetric;
	bool		init;
	u_int8_t	alpha;
	char		*color_str;
	int			min_displayed_z;
}	t_window;

void			update_image(t_window *window);
int				calulate_isometric_coordinates(t_input *input,
					int **xi, int **yi, t_window *window);
bool			fill_input(t_input *input, char *path);
void			handle_key_presses(mlx_key_data_t keydata, void *arg);
size_t			get_max_count(char *path);
bool			initialize_processing(t_input *input,
					int fd, char **line, int *i);
bool			process_lines(t_input *input, int fd, char *line, int i);
int				clean_exit(t_window *window);
mlx_t			*init_window(t_window *window);
void			draw(t_window *window, t_input *input, int *xi, int *yi);
void			get_color(t_color *color);
void			draw_straight_line(t_line *struc);
void			connect_points(t_line *struc);
void			init_rgba(t_color *color);
bool			free_arrays(double *a, double *b, int *c, int *d);
bool			give_input_feedback(void);
void			print_controls(void);
void			set_background_color(char *color_str,
					u_int32_t *pixels, u_int16_t alpha);

#endif