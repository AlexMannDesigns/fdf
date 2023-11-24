
#include "fdf.h"

int	map_parser_control(t_fdf *fdf, char *path)
{
	//int	fd;

	(void) fdf;

	if (path == NULL)
		return (print_error(RETURN_ERROR, ERROR_INVALID_FILE));	
	// check path points to a file, with extention '.fdf'
	// fd = open() ??


	// read line of map into buffer
	// check line length
	// check all chars numeric or whitespace
	return (RETURN_SUCCESS);
}

