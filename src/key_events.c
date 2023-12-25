
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

static void	move_image_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fdf->draw_values.x += 10;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fdf->draw_values.x -= 10;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fdf->draw_values.y += 10;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fdf->draw_values.y -= 10;
	return ;
}

static void	scale_image_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	int	scale;
	
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	{
		scale = fdf->draw_values.width * 0.1;
		if (scale == 0)
			scale = 1;
		fdf->draw_values.width += scale;
	}
	else if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
	{
		fdf->draw_values.width *= 0.9;
		if (fdf->draw_values.width == 0)
			fdf->draw_values.width = 1;
	}
	return ;
}

static void	gradient_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		fdf->draw_values.z += 1;
	else if (keydata.key == MLX_KEY_K && keydata.action == MLX_PRESS)
		fdf->draw_values.z -= 1;
	return ;
}

void	key_events(mlx_key_data_t keydata, void* fdf_ptr)
{
	// TODO add functionality for press and hold? 
	t_fdf	*fdf;

	fdf = (t_fdf *) fdf_ptr;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		move_image_event(fdf, keydata);
	else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		scale_image_event(fdf, keydata);
	else if (keydata.key == MLX_KEY_J || keydata.key == MLX_KEY_K)
		gradient_event(fdf, keydata);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(fdf->draw.mlx);
		exit(EXIT_SUCCESS);
	}
	re_draw_image(fdf);
	return ;
}
