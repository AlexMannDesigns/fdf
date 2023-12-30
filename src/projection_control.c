/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:02:15 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 14:02:38 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Handles the necessary geometry for plotting coordinates in isometric
 * projection.
 * We track the difference between current and original width so that z can
 * be scaled accordingly. This gives a zoom effect when the width increases in
 * size, rather than just stretching the image - i.e. the angles stay the same
 * unless the value of z is changed directly.
 */
static void	isometric_projection(t_draw *draw, int *x, int *y, int *z)
{
	float	_x;
	float	_y;
	float	_z;
	float	diff;


	// see math from
	//https://www.khanacademy.org/math/geometry/hs-geo-transformations/hs-geo-rotations/a/rotating-shapes
	// to rotate by 90 degrees
	// x = -y
	// y = x
	
	// 180 degrees
	// x = -x
	// y = -y

	// 270 degrees
	// x = y
	// y = -x 
	_x = (float) (*x) * draw->tile_width;
	_y = (float) (*y) * draw->tile_width;
	_z = (float) (*z) * draw->z_factor;


	diff = (float) draw->tile_width - draw->orig_width;
	_z *= (diff / draw->orig_width) + 1;
	//_z = -_z
	*x = draw->x_offset + (int) ((_x - _y) * COS_30);
	*y = draw->y_offset + (int) (-_z + (_x + _y) * SIN_30);


	/*
	TODO
	- Move the rotation math to a seperate helper function
	- Add variable to draw struct to monitor the rotation angle.
		- This can be changed with a keypress
	- Look into partial rotation (e.g. 45* instead of 90*) 
	*/
	//int temp;
	//temp = *x;
	// (90 - z must be positive)
	//*x = -(*y) + 300;
	//*y = temp;
	
	// (270)
	//*x = *y;
	//*y = 1000 + -temp;
	
	// (180 - z must be positive)
	//*x = 1000 + -(*x);
	//*y = 300 + -(*y);
	//
	
	printf("x = %d | y = %d\n", *x, *y);
	return ;
}

void	projection_control(t_draw *draw)
{
	// this might become an array of function pointers/jump table thing
	// As this is called twice per coord (once for drawing across, once for down)
	// we need a check to ensure we only do the projection math on the origin 
	// coord once.
	if (draw->current)
	{
		draw->current = FALSE;
		isometric_projection(draw, &(draw->x0), &(draw->y0), &(draw->z0));
	}
	isometric_projection(draw, &(draw->x1), &(draw->y1), &(draw->z1));
	return ;
}
