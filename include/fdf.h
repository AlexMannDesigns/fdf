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
# include <stdio.h>  // TODO delete

# include "libft.h"
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
# define ERROR_INVALID_LENGTH "Error: all lines must be of equal length"
# define ERROR_MALLOC "Error: malloc failed"
# define ERROR_MLX "Error: MLX42 function failed"

# define WIDTH 800 
# define HEIGHT 600
# define BPP sizeof(int32_t)
# define COLOUR 0XFF00FFFF
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
	struct s_coord	*next;
}					t_coord;

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

typedef struct s_rot
{
	int	w;
	int	h;
	int	i;
	int	j;
	int	temp;
}		t_rot;

/***** FUNCTIONS *****/

/* draw_wireframe.c */
void	draw_wireframe(t_fdf *fdf);

/* fdf_control.c */
void	fdf_control(t_fdf *fdf);

/* key_events.c */
void	key_events(mlx_key_data_t keydata, void *fdf_ptr);

/* map_parser.c */
int		map_parser_control(t_fdf *fdf, char *path);

/* plot_line.c */
void	plot_line(t_draw *draw);

/* projection_control.c */
void	projection_control(t_draw *draw);

/* utils.c */
int		print_error(int ret, char *msg);
int		free_and_exit(t_fdf *fdf);
void	draw_pixel(t_draw *draw, uint32_t x, uint32_t y);
int		new_image(mlx_t *mlx, mlx_image_t **img);

#endif
