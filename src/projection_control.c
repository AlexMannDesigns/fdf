
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

	_x = (float) (*x) * draw->tile_width;
	_y = (float) (*y) * draw->tile_width;
	_z = (float) (*z) * draw->z_factor;	

	diff = draw->tile_width - draw->orig_width;
	_z *= (diff / draw->orig_width) + 1;
	*x = draw->x_offset + (int) ((_x - _y) * COS_30);
	*y = draw->y_offset + (int) (-_z + (_x + _y) * SIN_30);
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
