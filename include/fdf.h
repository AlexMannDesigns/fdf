
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

# define USAGE_LONG "Welcome to FDF!\n\nUsage:\n./fdf [options...] [path-to-map]\n" \
	"\n" \
	"options:\n--help: displays this message\n" \
	"--test-parser: map will be parsed but fdf window will not open\n" \
	"\n" \
	"path-to-map:\n" \
	"Must be a file path to a valid fdf map, with file-extension '.fdf'"
# define USAGE "Usage:\n./fdf [options...] [path-to-map]"

# define ERROR_INVALID_OPTION "Error: invalid option. For help, use './fdf --help'"
# define ERROR_INVALID_FILE "Error: map file must be plain-text format and have '.fdf' extension"
# define ERROR_INVALID_PERMISSIONS "Error: map file could not be opened"
# define ERROR_INVALID_VALUES "Error: map must only contain numeric characters, spaces: ' ', and newlines: '\\n'"
# define ERROR_INVALID_LENGTH "Error: all lines must be of equal length"
# define ERROR_MALLOC "Error: malloc failed"

# define WIDTH 800
# define HEIGHT 512
# define BPP sizeof(int32_t)
# define COLOUR 0XFFFF00FF
#define COS_30 0.8660254
#define SIN_30 0.5



/***** STRUCTS *****/

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	struct s_coord	*next;
}			t_coord;

typedef struct s_fdf
{
	char	*error;
	int	width;
	size_t	path_idx;
	int	test_parser;
	int	help;
	int	exit_status;
	t_coord	*coord_list;
}		t_fdf;

typedef struct s_draw
{
	uint32_t	x0;
	uint32_t	y0;
	uint32_t	z0;
	uint32_t	x1;
	uint32_t	y1;
	uint32_t	z1;
	uint32_t	x_offset;
	uint32_t	y_offset;
	uint32_t	z_factor;
	uint32_t	tile_width;
	uint32_t	row;
	int		end_of_row;
	int		last_row;
	mlx_t		*mlx;
	mlx_image_t	*img;
}			t_draw;

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

/***** FUNCTIONS *****/

/* fdf_control.c */
void	fdf_control(t_fdf *fdf);

/* main.c */
void    print_array(char **arr); //TODO delete

/* map_parser.c */
int     map_parser_control(t_fdf *fdf, char *path);

/* plot_line.c */
void	plot_line(t_draw *draw, int drawing_down);

/* utils.c */
int	print_error(int ret, char *msg);
int     free_and_exit(t_fdf *fdf);

#endif
