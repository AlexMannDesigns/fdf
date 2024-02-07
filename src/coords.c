#include "fdf.h"
#include "libft.h"
#include <stdint.h>

/*
 * Handles memory allocation process for new node in coord list.
 * Either creates the start of a new list or adds to the final node
 * of an existing list.
 */
static int	coord_list_malloc(t_fdf *fdf, t_coord **coord)
{
	t_coord	*temp;

	temp = *coord;
	if (!(fdf->coord_list))
	{
		fdf->coord_list = (t_coord *) ft_memalloc(sizeof(t_coord));
		temp = fdf->coord_list;
	}
	else
	{
		temp = fdf->coord_list;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = (t_coord *) ft_memalloc(sizeof(t_coord));
		temp = temp->next;
	}
	*coord = temp;
	if (temp == NULL)
	{
		return (print_error(FALSE, ERROR_MALLOC));
	}
	return (TRUE);
}

// convert the hexadecimal string to an uint32_t
uint32_t	get_colour(char *hex)
{
	uint32_t	val;
	uint8_t		byte;
	size_t		i;

	// TODO must confirm hex string is valid (eg hex could be null here).
	val = 0;
	i = 0;
	while (hex[i])
	{
		byte = hex[i];
		if (byte >= '0' && byte <= '9')
		{
			byte = byte - '0';
		}
		else if (byte >= 'A' && byte <='F')
		{
			byte = byte - 'A' + 10;
		}
		val = (val << 4) | (byte & 0xF);
		i++;
	}
	if (i != 6)
	{
		return (val);
	}
	return ((val << 8) + 255);
}

/*
 * The coordinates for the image are added to a linked list, contained
 * in the t_fdf state struct.
 */
static int	add_coord(t_fdf *fdf, int i, int row, char *val)
{
	t_coord	*coord;
	char	*colour_str;

	if (!coord_list_malloc(fdf, &coord))
	{
		return (FALSE);
	}
	coord->x = i;
	coord->y = row;
	coord->z = ft_atoi(val);
	if (coord->z > MAX_VAL || coord->z < MIN_VAL)
	{
		return (print_error(FALSE, ERROR_INVALID_Z));
	}
	coord->colour = COLOUR; 
	colour_str = ft_strchr(val, ',');
	if (colour_str && colour_str + 1)
	{
		coord->colour = get_colour(ft_strchr(colour_str + 1, 'x') + 1);
	}
	return (TRUE);
}

static int	coords_check_width_and_height(t_fdf *fdf, int i, int row)
{
	if (fdf->width == 0)
	{
		fdf->width = i;
	}
	else if (fdf->width != i)
	{
		return (print_error(FALSE, ERROR_INVALID_LENGTH));
	}
	fdf->height = row;
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
int	create_coords(t_fdf *fdf, char *line)
{
	static int	row;
	char		**arr;
	int			i;

	arr = ft_strsplit(line, SPACE);
	if (arr == NULL)
	{
		return (print_error(FALSE, ERROR_MALLOC));
	}
	i = 0;
	while (arr[i])
	{
		if (!add_coord(fdf, i, row, arr[i]))
		{
			return (FALSE);
		}
		i++;
	}
	ft_free_char_array(&arr);
	++row;
	if (!coords_check_width_and_height(fdf, i, row))
	{
		return (FALSE);
	}
	return (TRUE);
}
