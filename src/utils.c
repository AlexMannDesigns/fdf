

#include "fdf.h"

/*
 * Frees any heap-allocated memory and then returns the exit value
 */
int	free_and_exit(t_fdf *fdf)
{
	t_coord	*coord;
	t_coord	*next;

	coord = fdf->coord_list;
	if (!coord)
		return (fdf->exit_status);
	while (coord)
	{
		next = coord->next;
		ft_memdel((void **)&coord);
		coord = next;
	}
	return (fdf->exit_status);
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

/*
 * Checks coord respect img boundaries before plotting a pixel there
 */
void	draw_pixel(t_draw *draw, uint32_t x, uint32_t y)
{
	if (
		x >= 0
		&& y >= 0
		&& x < draw->img->width
		&& y < draw->img->height
	)
		mlx_put_pixel(draw->img, x, y, COLOUR);
	return;
}
