/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:59:09 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 15:14:16 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * File-name for the map file must have extension '.fdf'
 * This function is a simple check for that.
 */
static int	validate_file_name(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || !ft_strequ(FDF_EXT, path + (len - 4)))
		return (FALSE);
	return (TRUE);
}

/*
 * The map file must only contain numeric characters and whitespace.
 */
static int	validate_line_chars(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line) && *line != SPACE)
			return (FALSE);
		line++;
	}
	return (TRUE);
}

/*
 * The coordinates for the image are added to a linked list, contained
 * in the t_fdf state struct.
 */
static int	add_coord(t_fdf *fdf, int i, int row, char *val)
{
	t_coord	*coord;

	if (!(fdf->coord_list))
	{
		fdf->coord_list = (t_coord *) ft_memalloc(sizeof(t_coord));
		coord = fdf->coord_list;
	}
	else
	{
		coord = fdf->coord_list;
		while (coord->next)
			coord = coord->next;
		coord->next = (t_coord *) ft_memalloc(sizeof(t_coord));
		coord = coord->next;
	}
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
	int			i;

	arr = ft_strsplit(line, SPACE);
	if (arr == NULL)
		return (print_error(FALSE, ERROR_MALLOC));
	i = 0;
	while (arr[i])
	{
		if (!add_coord(fdf, i, row, arr[i]))
			return (FALSE);
		i++;
	}
	ft_free_char_array(&arr);
	if (fdf->width == 0)
		fdf->width = i;
	else if (fdf->width != i)
		return (print_error(FALSE, ERROR_INVALID_LENGTH));
	++row;
	fdf->height = row;
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
	int		fd;
	char	*line;

	if (!validate_file_name(path))
		return (print_error(FALSE, ERROR_INVALID_FILE));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error(FALSE, ERROR_INVALID_PERMISSIONS));
	line = get_next_line(fd);
	while (line)
	{
		if (!validate_line_chars(line))
			return (print_error(FALSE, ERROR_INVALID_VALUES));
		if (!create_coords(fdf, line))
			return (FALSE);
		ft_strdel(&line);
		line = get_next_line(fd);
	}
	return (TRUE);
}
