
#include "fdf.h"

static void	isometric_projection(t_draw *draw, int *x, int *y, int *z)
{
	int	_x;
	int	_y;
	int	_z;
	
	_x = (*x) * draw->tile_width;
	_y = (*y) * draw->tile_width;
	_z = (*z) * draw->z_factor;	
	
	*x = draw->x_offset + (int) ((_x - _y) * COS_30);
	*y = draw->y_offset + (int) (-_z + (_x + _y) * SIN_30);
	return ;
}

void	projection_control(t_draw *draw)
{
	// this might become an array of function pointers/jump table thing
	if (draw->current)
	{
		draw->current = FALSE;
		isometric_projection(draw, &(draw->x0), &(draw->y0), &(draw->z0));
	}
	isometric_projection(draw, &(draw->x1), &(draw->y1), &(draw->z1));
	return ;
}
