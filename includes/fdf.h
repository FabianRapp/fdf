/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:29:17 by frapp             #+#    #+#             */
/*   Updated: 2023/12/31 01:10:09 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#define X_SIZE 1400
#define Y_SIZE 1400
#define X_IM_SIZE 1400
#define Y_IM_SIZE 1400

#define DIMETRIC_Y_DIVISOR 2
#define POINT_SIZE 3
#define X_OFFSET 0
#define Y_OFFSET 1
#define Z_OFFSET 2

#define ROTATION_INCREMENT (M_PI / 64)
#define ZOOM_IN_FACTOR 1.05
#define ZOOM_OUT_FACTOR 0.95
#define TRANSLATION_INCREMENT 2

// min 1, lower is better qulity but more cost
# ifndef GRAFIC_LVL
#  define GRAFIC_LVL 1
# endif

# include <stdlib.h>
# include <MLX42.h>
# include <libft.h>
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
	double	cos_angle;
	double	sin_angle;
	double	cos_elev;
	double	sin_elev;
	int		count;
} ;

typedef struct s_input
{
	int				x_max;
	int				y_max;
	int				z_min;
	int				z_max;
	int				*all_pts;
	float			zoom;
	int				trans_vec[3];
}	t_input;

struct	s_scaling_data
{
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
	int		translation_x_off;
	int		translation_y_off;
	int		count;
} ;

typedef struct s_img
{
	mlx_image_t	*ptr;
	int			*prj_x;
	int			*prj_y;
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
	uint8_t	alpha;
	char		*color_str;
	int			min_displayed_z;
}	t_window;

void			update_image(t_window *window);
int				calulate_isometric_coordinates(t_input *input,
					int **prj_x, int **prj_y, t_window *window);
bool			parser(t_input *input, char *path, bool dimetric);
void			handle_key_presses(mlx_key_data_t keydata, void *arg);
int				clean_exit(t_window *window);
mlx_t			*init_window(t_window *window);
void			draw(t_window *window, t_input *input, int *prj_x, int *prj_y);
void			get_color(t_color *color);
void			draw_straight_line(t_line *struc);
void			connect_points(t_line *struc);
void			init_rgba(t_color *color);
bool			free_on_fail(double **a, double **b, int **c, int **d);
bool			give_input_feedback(void);
void			print_controls(void);
void			set_background_color(char *color_str,
					uint32_t *pixels, uint16_t alpha);

void	scale_points(double *x, double *y, t_input *input, t_window *window);

#endif
