#include "fdf.h"
#include "libft.h"

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

/*
 * The coordinates for the image are added to a linked list, contained
 * in the t_fdf state struct.
 */
static int	add_coord(t_fdf *fdf, int i, int row, char *val)
{
	t_coord	*coord;

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
