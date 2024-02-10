/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:59:09 by amann             #+#    #+#             */
/*   Updated: 2024/02/10 17:09:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <fcntl.h>

/*
 * File-name for the map file must have extension '.fdf'
 * This function is a simple check for that.
 */
static int	validate_file_name(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || !ft_strequ(FDF_EXT, path + (len - 4)))
	{
		return (FALSE);
	}
	return (TRUE);
}

/*
 * The map file must only contain numeric characters and whitespace.
 */
static int	validate_line_chars(char *line)
{
	while (*line)
	{
		if (!ft_strchr(VALID_CHARS, *line))
		{
			return (FALSE);
		}
		line++;
	}
	return (TRUE);
}

static int	map_parser_loop(t_fdf *fdf, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!validate_line_chars(line))
		{
			ft_putstr_fd(ERROR_INVALID_VALUES_0, STDERR_FILENO);
			return (print_error(FALSE, ERROR_INVALID_VALUES_1));
		}
		if (!create_coords(fdf, line))
		{
			return (FALSE);
		}
		ft_strdel(&line);
		line = get_next_line(fd);
	}
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

	if (!validate_file_name(path))
	{
		ft_putstr_fd(ERROR_INVALID_FILE_0, STDERR_FILENO);
		return (print_error(FALSE, ERROR_INVALID_FILE_1));
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		return (print_error(FALSE, ERROR_INVALID_PERMISSIONS));
	}
	if (!map_parser_loop(fdf, fd))
	{
		return (FALSE);
	}
	return (TRUE);
}
