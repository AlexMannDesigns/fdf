
#include "fdf.h"

// TODO write a list of weird filenames and cmd line to test
/*
 * File-name for the map file must have extension '.fdf'
 * This function is a simple check for that.
 */
static int	validate_file_name(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || !ft_strequ(FDF_EXT, path + (len - 4)))
		return FALSE;
	return TRUE;
}

/*
 * The map file must only contain numeric characters and whitespace.
 */
static int	validate_line_chars(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line) && !ft_iswhitespace(*line))
			return (FALSE);
		line++;
	}
	return (TRUE);
}

/*
 * The coordinates for the image are added to a linked list, contained
 * in the t_fdf state struct.
 */
static int	add_coord(t_coord *coord, int i, int row, char *val)
{
	if (coord)
	{
		while (coord->next)
			coord = coord->next;
	}
	coord = (t_coord *) ft_memalloc(sizeof(t_coord));
	if (coord == NULL)
		return (print_error(FALSE, ERROR_MALLOC));
	coord->x = i;
	coord->y = row;
	coord->z = ft_atoi(val);	
	return (TRUE);
}

/*
 * Control function for adding coordinates to list, once the map file has been
 * validated. Each line is split into a 2D array of coord values. These are
 * then added to the coord_list by a helper function.
 * The x and y coords are represented by the position of the value in the 2D
 * array. The z coord is the value.
 * We do not allow for uneven line lengths, the image must be a rectangle. This
 * is tracked by a static var.
 */
static int	create_coords(t_fdf *fdf, char *line)
{
	static int	row;
	char		**arr;
	int		i;

	arr = ft_strsplit(line, ' ');
	if (arr == NULL)
		return (print_error(FALSE, ERROR_MALLOC));
	i = 0;
	while (arr[i])
	{
		if (!add_coord(fdf->coord_list, i, row, arr[i]))
			return (FALSE);
		i++;
	}
	if (fdf->width == 0)
		fdf->width = i;
	else if (fdf->width != i)
		return (print_error(FALSE, ERROR_INVALID_LENGTH));
	++row;
	return (TRUE);
}

/*
 * Before drawing anything, we must parse the necessary data from the .fdf
 * 'map' file.
 * We need to check all of the following:
 *	- The path to the file is valid.
 *	- The file has a '.fdf' extension and can be opened.
 *	- The file only contains numeric and whitespace characters.
 *	- Each line in the file is of equal length.
 * Once validated, we organise the values into a linked list.
 */
int	map_parser_control(t_fdf *fdf, char *path)
{
	int	fd;
	int	gnl_ret;
	char	*line;

	if (path == NULL)
		return (print_error(FALSE, USAGE));	
	if (!validate_file_name(path))
		return (print_error(FALSE, ERROR_INVALID_FILE));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error(FALSE, ERROR_INVALID_PERMISSIONS));
	gnl_ret = get_next_line(fd, &line);  //TODO re-build a simplified GNL, nb handle malloc errors
	while (gnl_ret)
	{
		printf("%s length :%zu\n", line, ft_strlen(line));
		if (!validate_line_chars(line))
			return (print_error(FALSE, ERROR_INVALID_VALUES));
		if (!create_coords(fdf, line))
			return (FALSE); 	
		ft_strdel(&line);
		gnl_ret = get_next_line(fd, &line);
	}
	return (TRUE);
}
