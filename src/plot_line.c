
#include "fdf.h"

/*
 * Plots either a horizontal or vertical line. In some situations 'a' will be 
 * 'ahead' of 'b', for example when drawing an isometric projection. The
 * sign variable takes care of this.
 */
static int	draw_horizontal_vertical(t_draw *d, int a, int b, int x)
{
	int	sign;

	sign = 1;
	if (a > b)
		sign = -1;
	if (x)
	{
		while (a != b)
		{
			draw_pixel(d, (uint32_t) a, (uint32_t) d->y0);
			a += sign;
		}
	}
	else
	{
		while (a != b)
		{
			draw_pixel(d, (uint32_t) d->x0, (uint32_t) a);
			a += sign;
		}
	}
	return (TRUE);	
}

/*
 * No algo needed if the points are level (either horizontally or vertically).
 * We can just increment/decrement the x or y value in a loop, plotting pixels
 * as we go.
 */
static int	check_horizontal_and_vertical(t_draw *draw)
{
	if (draw->y0 == draw->y1)
		return (draw_horizontal_vertical(draw,
						draw->x0,
						draw->x1,
						TRUE));
	if (draw->x0 == draw->x1)
		return (draw_horizontal_vertical(draw,
						draw->y0,
						draw->y1,
						FALSE));
	return (FALSE);
}

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

	projection_control(draw);
	if (check_horizontal_and_vertical(draw))
		return ;
	plot_line_setup(draw, &algo);
	while (TRUE)
	{
		draw_pixel(draw, algo.x, algo.y);
		if (!bresenham(&algo, draw))
			break ;
	}
	return ;
}

