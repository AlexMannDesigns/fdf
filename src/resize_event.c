#include "fdf.h"
#include <stdlib.h>

/*
 * When the window is resized, the background must be re-drawn with the new dimensions,
 * gathered from the mlx42 event hook. We then also need to redraw the wireframe on top
 * of the background.
 */
void	resize_event(int32_t width, int32_t height, void* fdf_ptr)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) fdf_ptr;
	mlx_delete_image(fdf->draw.mlx, fdf->draw.img);
	mlx_delete_image(fdf->draw.mlx, fdf->draw.img);
	fdf->draw.current_win_h = height;
	fdf->draw.current_win_w = width;
	draw_background(&(fdf->draw), fdf->draw.current_win_h, fdf->draw.current_win_w);
	if (!new_image(fdf->draw.mlx, &(fdf->draw.img), fdf->draw))
	{
		mlx_terminate(fdf->draw.mlx);
		exit(EXIT_FAILURE);
	}
	draw_wireframe(fdf);
	return ;
}
