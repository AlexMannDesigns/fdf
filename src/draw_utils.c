#include "fdf.h"
#include "MLX42/MLX42.h"
#include "libft.h"

void	re_draw_image(t_fdf *fdf)
{
	mlx_delete_image(fdf->draw.mlx, fdf->draw.img);
	if (!new_image(fdf->draw.mlx, &(fdf->draw.img)))
	{
		mlx_terminate(fdf->draw.mlx);
		exit(EXIT_FAILURE);
	}
	draw_wireframe(fdf);
	return ;
}

/*
 * Checks coord respect img boundaries before plotting a pixel there
 */
void	draw_pixel(t_draw *draw, uint32_t x, uint32_t y)
{
	if (
		draw->img
		&& x >= 0 && y >= 0
		&& x < WIDTH && y < HEIGHT
	)
	{
		draw->img_visible = TRUE;
		mlx_put_pixel(draw->img, x, y, COLOUR);
	}
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
		
/*
 * Finds the actual width of an isometric projection
 */
int	get_actual_width(int tile_width, int height, int width)
{
	 return (tile_width * (height + width) * ROOT_3 / 2);
}

/*
 * Finds the actual height of an isometric projection
 */
int	get_actual_height(int tile_width, int height, int width)
{
	return (tile_width * (height + width) / 2);
}
