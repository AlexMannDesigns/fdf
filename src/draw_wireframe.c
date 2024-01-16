/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:47:52 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 13:51:42 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * This is where we set up the variables needed to draw the wireframe. The
 * width handles the size of the image, offsets where it is placed in the
 * window and the z-factor handles how severe the gradients are.
 */
static int	draw_setup(t_fdf *fdf, t_draw *draw)
{
	draw->last_row = FALSE;
	draw->y_offset = fdf->draw_values.y;
	draw->tile_width = fdf->draw_values.width;
	draw->x_offset = fdf->draw_values.x;
	draw->z_factor = fdf->draw_values.z;
	return (TRUE);
}

/*
 * The x,y,z coords from the next node are taken to give us the end point of
 * the horizontal line. The exception being when we get to the end of the row
 * which is checked at the start of the function.
 */
static int	find_next_point_across(t_draw *draw, t_coord *current)
{
	t_coord	*next;

	next = current->next;
	if (next->x == 0)
		return (FALSE);
	draw->x1 = next->x;
	draw->y1 = next->y;
	draw->z1 = next->z;
	// scale_points();
	projection_control(draw, &(draw->x1), &(draw->y1), &(draw->z1));
	draw->x1 += draw->x_offset;
	draw->y1 += draw->y_offset;
	return (TRUE);
}

/*
 * For each point, we also draw down to the point at the same x axis but on the
 * y axis + 1. This means we need to loop forward in coord nodes by the width
 * of the image. A flag has been added to optimise the final row. We no longer
 * need to draw down to the next row once we have reached the final row.
 */
static int	find_next_point_down(t_draw *draw, t_coord *current, int width)
{
	t_coord	*next;
	int		i;

	if (draw->last_row)
		return (FALSE);
	i = 0;
	next = current;
	while (i < width)
	{
		next = next->next;
		if (!next)
		{
			draw->last_row = TRUE;
			return (FALSE);
		}
		i++;
	}
	draw->x1 = next->x;
	draw->y1 = next->y;
	draw->z1 = next->z;
	// scale_points();
	projection_control(draw, &(draw->x1), &(draw->y1), &(draw->z1));
	draw->x1 += draw->x_offset;
	draw->y1 += draw->y_offset;
	return (TRUE);
}

/*
 * Takes x,y,z values of the current coord. Sets 'current' flag in the draw
 * struct to ensure projection calcs are only completed on its values once.
 */
static void	set_current_point(t_draw *draw, t_coord *current)
{
	draw->current = TRUE; // TODO get rid of this - find better way to implement projection calc
	draw->x0 = current->x;
	draw->y0 = current->y;
	draw->z0 = current->z;
	// scale_points();
	projection_control(draw, &(draw->x0), &(draw->y0), &(draw->z0));
	draw->x0 += draw->x_offset;
	draw->y0 += draw->y_offset;
	return ;
}

/*
 * This is 'where the magic happens'.
 * We loop through the coord list, at each point mapping out
 * the next coordinate across and down, and plotting lines between them,
 * until we reach the end of the image.
 */
void	draw_wireframe(t_fdf *fdf)
{
	t_coord	*current;
	t_draw	*draw;

	draw = &(fdf->draw);
	if (!draw->mlx || !draw->img || !draw_setup(fdf, draw))
		return ;
	current = fdf->coord_list;
	while (current && current->next)
	{
		set_current_point(draw, current);
		if (find_next_point_across(draw, current))
			plot_line(draw);
		if (find_next_point_down(draw, current, fdf->width))
			plot_line(draw);
		current = current->next;
	}
	return ;
}
