
#include "fdf.h"

static void	re_draw_image(t_fdf *fdf)
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

void	key_events(mlx_key_data_t keydata, void* fdf_ptr)
{
	//TODO add functionality for press and hold? 
	t_fdf	*fdf;

	fdf = (t_fdf *) fdf_ptr;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fdf->draw_values.x += 10;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fdf->draw_values.x -= 10;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fdf->draw_values.y += 10;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fdf->draw_values.y -= 10;
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		fdf->draw_values.width *= 1.05;
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		fdf->draw_values.width *= 0.95;
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		fdf->draw_values.z += 1;
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_PRESS)
		fdf->draw_values.z -= 1;
	re_draw_image(fdf);
	return ;
}

