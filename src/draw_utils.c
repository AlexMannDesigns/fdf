#include "fdf.h"
#include "MLX42/MLX42.h"
#include "libft.h"
#include <stdint.h>

void	re_draw_image(t_fdf *fdf)
{
	mlx_delete_image(fdf->draw.mlx, fdf->draw.img);
	if (!new_image(fdf->draw.mlx, &(fdf->draw.img), fdf->draw))
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
void	draw_pixel(t_draw *draw, t_pixel pixel) 
{
	if (
		pixel.img
		&& pixel.x >= 0 && pixel.y >= 0
		&& pixel.x < (int) draw->current_win_w
		&& pixel.y < (int) draw->current_win_h 
	)
	{
		draw->img_visible = TRUE;
		// printf("%u\n", pixel.colour);
		mlx_put_pixel(
			pixel.img,
			(uint32_t) pixel.x,
			(uint32_t) pixel.y,
			pixel.colour
		);
	}
	return ;
}

/*
 * Generates a new mlx image and draws it to the window.
 */
int	new_image(mlx_t *mlx, mlx_image_t **img, t_draw draw)
{
	*img = mlx_new_image(mlx, draw.current_win_w, draw.current_win_h);
	if (!img)
	{
		return (print_error(FALSE, ERROR_MLX));
	}
	if (mlx_image_to_window(mlx, *img, 0, 0) == -1)
	{
		return (print_error(FALSE, ERROR_MLX));
	}
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
