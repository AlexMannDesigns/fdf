/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:05:44 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 15:14:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/***** LIBRARIES *****/

# include <fcntl.h>
#include <stdint.h>
# include <stdio.h>  // TODO delete

# include "MLX42/MLX42.h"

/***** CONSTANTS *****/

# define RETURN_SUCCESS 0
# define RETURN_ERROR 1

# define TRUE 1
# define FALSE 0

# define SPACE ' '

# define FDF_EXT ".fdf"

# define HELP_FLAG "--help"
# define TEST_PARSER "--test-parser"

# define USAGE_LONG "Welcome to FDF!\n\nUsage:\n" \
	"./fdf [options...] [path-to-map]\n" \
	"\n" \
	"options:\n--help: displays this message\n" \
	"--test-parser: map will be parsed but fdf window will not open\n" \
	"\n" \
	"path-to-map:\n" \
	"Must be a file path to a valid fdf map, with file-extension '.fdf'"
# define USAGE "Usage:\n./fdf [options...] [path-to-map]"

# define ERROR_INVALID_OPTION "Error: invalid option. For help, use " \
	"'./fdf --help'"
# define ERROR_INVALID_FILE "Error: map file must be plain-text format and " \
	"have '.fdf' extension"
# define ERROR_INVALID_PERMISSIONS "Error: map file could not be opened"
# define ERROR_INVALID_VALUES "Error: map must only contain numeric " \
	"characters, spaces: ' ', and newlines: '\\n'"
# define ERROR_INVALID_Z "Error: z values must be between INT16_MIN and INT16_MAX"
# define ERROR_INVALID_LENGTH "Error: all lines must be of equal length"
# define ERROR_NO_VALUES "Error: no coordinates in file"
# define ERROR_MALLOC "Error: malloc failed"
# define ERROR_MLX "Error: MLX42 function failed"

# define VALID_CHARS "-0123456789AaBbCcDdEeFfXx, \n"
# define MAX_VAL 32767
# define MIN_VAL -32768
# define WIDTH 800 
# define HEIGHT 600
# define BPP sizeof(int32_t)
# define COLOUR 0XFFFFFFFF
# define BLACK 0X000000FF
# define COS_30 0.8660254
# define SIN_30 0.5
# define ROOT_3 1.7320508

/***** STRUCTS *****/

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	uint32_t	colour;
	struct s_coord	*next;
}			t_coord;

typedef struct s_projection
{
	float	_x;
	float	_y;
	float	_z;
	float	diff;
}		t_projection;

typedef struct s_draw
{
	int		x0;
	int		y0;
	int		z0;
	int		x1;
	int		y1;
	int		z1;
	int		current;
	int		x_offset;
	int		y_offset;
	int		z_factor;
	int		tile_width;
	int		last_row;
	int		orig_width;
	int		img_visible;
	uint32_t	current_win_h;
	uint32_t	current_win_w;
	t_projection	p;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*bg;
}			t_draw;

typedef struct s_draw_values
{
	int	x;
	int	y;
	int	z;
	int	width;
}		t_draw_values;

typedef struct s_fdf
{
	char		*error;
	int		width;
	int		height;
	size_t		path_idx;
	int		test_parser;
	int		help;
	int		exit_status;
	int		rotate_angle;
	int		move;
	t_coord		*coord_list;
	t_draw		draw;
	t_draw_values	draw_values;
}					t_fdf;

typedef struct s_algo
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;
}		t_algo;

typedef struct s_pixel
{
	int		x;
	int		y;
	uint32_t	colour;
	mlx_image_t	*img;
}			t_pixel;

/***** FUNCTIONS *****/

/* coords.c */
int	create_coords(t_fdf *fdf, char *line);

/* draw_background.c */
int	draw_background(t_draw *draw, uint32_t height, uint32_t width);

/* draw_wireframe.c */
void	draw_wireframe(t_fdf *fdf);

/* draw_utils.c */
void	draw_pixel(t_draw *draw, t_pixel pixel); 
int	new_image(mlx_t *mlx, mlx_image_t **img, t_draw draw);
int	get_actual_height(int tile_width, int height, int width);
int	get_actual_width(int tile_width, int height, int width);
void	re_draw_image(t_fdf *fdf);

/* fdf_control.c */
void	fdf_control(t_fdf *fdf);

/* key_events.c */
void	key_events(mlx_key_data_t keydata, void *fdf_ptr);

/* map_parser.c */
int		map_parser_control(t_fdf *fdf, char *path);

/* plot_line.c */
void	plot_line(t_draw *draw, uint32_t colour);

/* projection_control.c */
void	projection_control(t_draw *draw, int *x, int *y, int *z);

/* resize_event.c */
void	resize_event(int32_t width, int32_t height, void* fdf_ptr);

/* utils.c */
int		print_error(int ret, char *msg);
int		free_and_exit(t_fdf *fdf);

#endif
