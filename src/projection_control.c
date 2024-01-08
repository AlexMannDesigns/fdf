/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:02:15 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 15:12:39 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	scale_points(t_draw *draw, int *x, int *y, int *z)
{
	draw->p._x = (float) (*x) * draw->tile_width;
	draw->p._y = (float) (*y) * draw->tile_width;
	draw->p._z = (float) (*z) * draw->z_factor;
	draw->p.diff = (float) draw->tile_width - draw->orig_width;
	draw->p._z *= (float) ((draw->p.diff / draw->orig_width) + 1);
	return ;
}

/*
 * Handles the necessary geometry for plotting coordinates in isometric
 * projection.
 * We track the difference between current and original width so that z can
 * be scaled accordingly. This gives a zoom effect when the width increases in
 * size, rather than just stretching the image - i.e. the angles stay the same
 * unless the value of z is changed directly.
 */
static void	isometric_projection(t_draw *draw, int *x, int *y)
{
	*x = (int) ((draw->p._x - draw->p._y) * COS_30);
	*y = (int) (-(draw->p._z) + (draw->p._x + draw->p._y) * SIN_30);
	return ;
}

void	projection_control(t_draw *draw, int *x, int *y, int *z)
{
	scale_points(draw, x, y, z);
	isometric_projection(draw, x, y); 
	return ;
}
