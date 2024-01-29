#include "fdf.h"

/*
 * We need to specify that each pixel is set to black before creating a new
 * mlx image instance on top of it within which the wireframe will be drawn.
 * This is called during the setup of the program or when the window is 
 * resized, to loop through every column and row setting each pixel to black.
 */
int	draw_background(t_draw *draw, uint32_t height, uint32_t width)
{
	t_pixel	pixel;

	if (!new_image(draw->mlx, &(draw->bg), *draw))
	{
		return (FALSE);
	}
	pixel.colour = BLACK;
	pixel.img = draw->bg;
	pixel.y = 0;
	while (pixel.y < (int) height)
	{
		pixel.x = 0;
		while (pixel.x < (int) width)
		{
			draw_pixel(draw, pixel);
			(pixel.x)++;
		}
		(pixel.y)++;
	}
	return (TRUE);
}

