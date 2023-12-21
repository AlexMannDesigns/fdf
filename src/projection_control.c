
#include "fdf.h"

/*
 * Handles the necessary geometry for plotting coordinates in isometric
 * projection.
 */
static void	isometric_projection(t_draw *draw, int *x, int *y, int *z)
{
	float	_x;
	float	_y;
	float	_z;
	float	diff;

	// TODO may need to separate out some of the math here
	// Multiplying these values up leads to image stretching rather than scaling
	// when zooming in and out, changing the slope angles
	// zooming also gets 'slower' as the image gets bigger
	// perhaps the width/z-factor math should be handled elsewhere and applied differently

	// increment z_factor by % change in width??
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
