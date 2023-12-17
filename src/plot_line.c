
#include "fdf.h"

/*
 * This is the setup for bresenham's line drawing algo.
 * We need the difference in value between the xy coords of the two points.
 * We also need to determine the direction that the line goes.
 */
static void	plot_line_setup(t_draw *draw, t_algo *algo)
{
	ft_bzero((void *) algo, sizeof(t_algo));
	algo->dx = ft_abs(draw->x1 - draw->x0);
	algo->dy = -(ft_abs(draw->y1 - draw->y0));
	algo->x = (int) draw->x0;
	algo->y = (int) draw->y0;
	algo->sx = 1;
	algo->sy = 1;
	if (algo->x > (int) draw->x1)
		algo->sx = -1;
	if (algo->y > (int) draw->y1)
		algo->sy = -1;
	algo->error = algo->dx + algo->dy;
	return ;
}

/*
 * Checks that the x and y coords respect the boundaries of the mlx image
 * before attempting to plot them.
 * Casting values to int is safe because we set limits for these in
 * fdf_control.c::draw_setup 
 */
static int	check_boundaries(t_draw *draw, int x, int y)
{
	if (
		x >= 0
		&& y >= 0
		&& x < (int) draw->img->width
		&& y < (int) draw->img->height
	)
		return (TRUE);
	return (FALSE);
}

/*
 * My implementation of Bresenham's line drawing algo.
 * In essence, we are moving pixel by pixel between the two xy coords at the
 * beginning and end of each line. This algo determines whether we use the
 * next pixel across or down in order to estimate a straight line through
 * the grid.
 */
static int bresenham(t_algo *algo, t_draw *draw)
{
	if (algo->x == (int) draw->x1 && algo->y == (int) draw->y1)
		return (FALSE);
	algo->e2 = 2 * algo->error;
	if (algo->e2 >= algo->dy)
	{
		if (algo->x == (int) draw->x1)
			return (FALSE);
		algo->error += algo->dy;
		algo->x += algo->sx;
	}
	if (algo->e2 <= algo->dx)
	{
		if (algo->y == (int) draw->y1)
			return (FALSE);
		algo->error += algo->dx;
		algo->y += algo->sy;
	}
	return (TRUE);
}

/*
 * Called in a loop from fdf_control, handles the drawing of a line between
 * two points in the image.
 */
void	plot_line(t_draw *draw)
{
	t_algo	algo;

	plot_line_setup(draw, &algo);
//	ft_putendl("***");
	while (TRUE)
	{
		//printf("x = %d y = %d p = %d\n", x, y, p);
		if (check_boundaries(draw, algo.x, algo.y))
		{
			mlx_put_pixel(
				draw->img,
				(uint32_t) algo.x,
				(uint32_t) algo.y,
				COLOUR
			);
		}
		if (!bresenham(&algo, draw))
			break ;
	}
	return ;
}

