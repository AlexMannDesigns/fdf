
#ifndef FDF_H
# define FDF_H

/***** LIBRARIES *****/

# include "libft.h"


/***** CONSTANTS *****/

# define RETURN_SUCCESS 0
# define RETURN_ERROR 1

# define USAGE "Welcome to FDF!\n\nUsage:\n./fdf [options...] [path-to-map]\n" \
	"\n" \
	"options:\n--help: displays this message\n" \
	"--test-parser: map will be parsed but fdf window will not open\n" \
	"\n" \
	"path-to-map:\n" \
	"Must be a file path to a valid fdf map, with file-extension '.fdf'"


# define HELP_FLAG "--help"
# define TEST_PARSER "--test-parser"

# define ERROR_INVALID_FILE "Error: map file must be plain-text format and have '.fdf' extension"
# define ERROR_INVALID_PERMISSIONS "Error: map file could not be opened"
# define ERROR_INVALID_VALUES "Error: map must only contain numeric characters"
# define ERROR_INVALID_LENGTH "Error: all lines must be of equal length"


/***** STRUCTS *****/


typedef struct s_fdf
{
	char	*error;	
}		t_fdf;

#endif
