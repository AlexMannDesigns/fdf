
#include "fdf.h"


// TODO re-implement RETURN_SUCCESS/ERROR as EXIT_SUCCESS/FAILURE ??
// TODO check neither WIDTH nor HEIGHT exceed int_max, or some arbitrary lower value,
// e.g. something reasonable given the dimensions of modern monitors

/**
 * This is where we set up the window, and mlx background img.
 * The background image is set to black, pixel by pixel, when the program
 * starts. We then set up a new, transparent layer, which will be overlayed
 * on the background for the wireframe to be drawn on.
 */
int	mlx_setup(t_draw *draw)
{
	uint32_t	i;
	uint32_t	j;
	
	ft_bzero((void *) draw, sizeof(t_draw));
	draw->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!draw->mlx)
		return (FALSE); // Error handling for mlx42 needed	
	draw->bg = mlx_new_image(draw->mlx, WIDTH, HEIGHT); // can mlx_new_image() fail? 
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			mlx_put_pixel(draw->bg, j++, i, BLACK);
		i++;
	}
	mlx_image_to_window(draw->mlx, draw->bg, 0, 0); //draw image from top left corner
	draw->img = mlx_new_image(draw->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(draw->mlx, draw->img, 0, 0); //draw image from top left corner
	return (TRUE);
}

void	set_fdf_values(mlx_key_data_t keydata, void* fdf_ptr)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) fdf_ptr;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		fdf->draw_values.x += 5;	
	draw_wireframe(fdf);
	return ;
}

/*
 * Control loop which handles the setup of the mlx functionality. 
 * Here we create our window and call our hooks. We also call the draw
 * function which handles the creation of the wireframe image itself.
 */
void	fdf_control(t_fdf *fdf)
{	
	if (!mlx_setup(&(fdf->draw)))
		return ;
	mlx_key_hook(fdf->draw.mlx, &set_fdf_values, (void *) fdf);
	fdf->draw_values.width = 20;
	fdf->draw_values.z = 3;
	draw_wireframe(fdf);
	mlx_loop(fdf->draw.mlx);
	mlx_terminate(fdf->draw.mlx);
	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
