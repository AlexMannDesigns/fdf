#include "fdf.h"

static int	get_colour(t_draw *draw)
{
	(void) draw;
	return COLOUR;
}

/*
 * Checks coord respect img boundaries before plotting a pixel there
 */
void	draw_pixel(t_draw *draw, uint32_t x, uint32_t y)
{
	if (
		draw->img
		&& x >= 0
		&& y >= 0
		&& x < WIDTH
		&& y < HEIGHT
	)
		mlx_put_pixel(draw->img, x, y, get_colour(draw));
	return ;
}

/*
 * Generates a new mlx image and draws it to the window.
 */
int	new_image(mlx_t *mlx, mlx_image_t **img)
{
	*img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (print_error(FALSE, ERROR_MLX));
	if (mlx_image_to_window(mlx, *img, 0, 0) == -1)
		return (print_error(FALSE, ERROR_MLX));
	return (TRUE);
}
