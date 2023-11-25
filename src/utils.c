

#include "fdf.h"

/*
 * Frees any heap-allocated memory and then returns the exit value
 */
int	free_and_exit(t_fdf *fdf, int value)
{
	t_coord	*coord;
	t_coord	*next;

	coord = fdf->coord_list;
	if (!coord)
		return (value);
	while (coord)
	{
		next = coord->next;
		ft_memdel((void **)&coord);
		coord = next;
	}
	return (value);
}


/*
 * All-purpose error message printer
 * Prints 'msg' to STDERR, followed by NL, and then returns 'ret'
 */
int	print_error(int ret, char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (ret);
}
