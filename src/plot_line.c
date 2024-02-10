/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:01:19 by amann             #+#    #+#             */
/*   Updated: 2024/02/10 17:05:21 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

/*
 * Plots either a horizontal or vertical line. In some situations 'a' will be
 * 'ahead' of 'b', for example when drawing an isometric projection. The
 * sign variable takes care of this.
 */
static void	draw_horizontal_vertical(t_draw *d, t_pixel *pixel, int x)
{
	int	sign;

	pixel->img = d->img;
	sign = 1;
	if (pixel->a > pixel->b)
	{
		sign = -1;
	}
	while (pixel->a != pixel->b)
	{
		pixel->x = d->x0;
		pixel->y = pixel->a;
		if (x)
		{
			pixel->x = pixel->a;
			pixel->y = d->y0;
		}
		draw_pixel(d, *pixel);
		pixel->a += sign;
	}
	return ;
}

/*
 * No algo needed if the points are level (either horizontally or vertically).
 * We can just increment/decrement the x or y value in a loop, plotting pixels
 * as we go.
 */
static int	check_horizontal_and_vertical(t_draw *d, uint32_t colour)
{
	t_pixel	pixel;

	pixel.colour = colour;
	if (d->y0 == d->y1)
	{
		pixel.a = d->x0;
		pixel.b = d->x1;
		draw_horizontal_vertical(d, &pixel, TRUE);
		return (TRUE);
	}
	if (d->x0 == d->x1)
	{
		pixel.a = d->y0;
		pixel.b = d->y1;
		draw_horizontal_vertical(d, &pixel, FALSE);
		return (TRUE);
	}
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
	{
		algo->sx = -1;
	}
	if (algo->y > (int) draw->y1)
	{
		algo->sy = -1;
	}
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
static int	bresenham(t_algo *algo, t_draw *draw)
{
	if (algo->x == (int) draw->x1 && algo->y == (int) draw->y1)
	{
		return (FALSE);
	}
	algo->e2 = 2 * algo->error;
	if (algo->e2 >= algo->dy)
	{
		if (algo->x == (int) draw->x1)
		{
			return (FALSE);
		}
		algo->error += algo->dy;
		algo->x += algo->sx;
	}
	if (algo->e2 <= algo->dx)
	{
		if (algo->y == (int) draw->y1)
		{
			return (FALSE);
		}
		algo->error += algo->dx;
		algo->y += algo->sy;
	}
	return (TRUE);
}

/*
 * Called in a loop from fdf_control, handles the drawing of a line between
 * two points in the image.
 */
void	plot_line(t_draw *draw, uint32_t colour)
{
	t_algo	algo;
	t_pixel	pixel;

	pixel.colour = colour;
	pixel.img = draw->img;
	if (check_horizontal_and_vertical(draw, colour))
	{
		return ;
	}
	plot_line_setup(draw, &algo);
	while (TRUE)
	{
		pixel.x = algo.x;
		pixel.y = algo.y;
		draw_pixel(draw, pixel);
		if (!bresenham(&algo, draw))
		{
			break ;
		}
	}
	return ;
}
