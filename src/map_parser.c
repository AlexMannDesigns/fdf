
#include "fdf.h"

// TODO write a list of weird filenames and cmd line to test
static int	validate_file_name(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || !ft_strequ(FDF_EXT, path + (len - 4)))
		return FALSE;
	return TRUE;
}

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

void	print_array(char **arr)
{
	for (int i = 0 ; arr[i] ; i++)
		printf("%s\n", arr[i]);
}

static int	create_coords(t_fdf *fdf, char *line)
{
	char	**arr;

	(void) fdf;
	arr = ft_strsplit(line, ' ');
	if (arr == NULL)
		return (print_error(FALSE, ERROR_MALLOC));
	// print_array(arr);		
	
	return (TRUE);
}

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
	//printf("%s", line);

	// read line of map into buffer
	// check line length
	// check all chars numeric or whitespace
}

