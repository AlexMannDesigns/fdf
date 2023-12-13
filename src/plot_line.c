
#include "fdf.h"


void	plot_line(t_draw *draw, int drawing_down)
{
	// line drawing algo goes here
	int	x, y, dx, dy, sx, sy, error, e2;

	if (draw->end_of_row)
	{
		draw->end_of_row = FALSE;
		return ;
	}
	if (drawing_down && draw->last_row)
		return ;
	dx = ft_abs(draw->x1 - draw->x0);
	dy = -(ft_abs(draw->y1 - draw->y0));
	x = (int) draw->x0;
	y = (int) draw->y0;
	sx = 1;
	sy = 1;
	if (x > (int) draw->x1)
		sx = -1;
	if (y > (int) draw->y1)
		sy = -1;
	error = dx + dy;

//	ft_putendl("***");
	while (TRUE)
	{
		//printf("x = %d y = %d p = %d\n", x, y, p);
		mlx_put_pixel(draw->img, x, y, COLOUR);
		if (x == (int) draw->x1 && y == (int) draw->y1)
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if (x == (int) draw->x1)
				break ;
			error = error + dy;
			x = x + sx;
		}
		if (e2 <= dx)
		{
			if (y == (int) draw->y1)
				break ;
			error = error + dx;
			y = y + sy;
		}
	}
	return ;
}

