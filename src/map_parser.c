
#include "fdf.h"

// TODO write a list of weird filenames and cmd line to test
int	validate_file_name(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || !ft_strequ(FDF_EXT, path + (len - 4)))
		return FALSE;
	return TRUE;
}

int	map_parser_control(t_fdf *fdf, char *path)
{
	//int	fd;

	(void) fdf;

	if (path == NULL)
		return (print_error(RETURN_ERROR, USAGE));	
	if (!validate_file_name(path))
		return (print_error(RETURN_ERROR, ERROR_INVALID_FILE));

	// check path points to a file, with extention '.fdf'
	// fd = open() ??


	// read line of map into buffer
	// check line length
	// check all chars numeric or whitespace
	return (RETURN_SUCCESS);
}

