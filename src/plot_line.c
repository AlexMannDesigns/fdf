
#include "fdf.h"

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

static int	check_end(t_draw *draw, int drawing_down)
{
	if (draw->end_of_row)
	{
		draw->end_of_row = FALSE;
		return (TRUE);
	}
	if (drawing_down && draw->last_row)
		return (TRUE);
	return (FALSE);
}

/*
 * Checks that the x and y coords respect the boundaries of the mlx image
 * before attempting to plot them.
 * Casting values to int is safe because we set limits for these in
 * fdf_control.c::draw_setup 
 */
static int	check_boundaries(t_draw *draw, int x, int y)
{
	if (x >= 0 && y >= 0
		&& x < (int) draw->img->width && y < (int) draw->img->height)
		return (TRUE);
	return (FALSE);
}

/*
 * My implementation of Bresenham's line drawing algo.
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
void	plot_line(t_draw *draw, int drawing_down)
{
	// line drawing algo goes here
	t_algo	algo;
	
	if (check_end(draw, drawing_down))
		return ;
	plot_line_setup(draw, &algo);
//	ft_putendl("***");
	while (TRUE)
	{
		//printf("x = %d y = %d p = %d\n", x, y, p);
		if (check_boundaries(draw, algo.x, algo.y))
			mlx_put_pixel(draw->img, algo.x, algo.y, COLOUR);
		if (!bresenham(&algo, draw))
			break ;
	}
	return ;
}

