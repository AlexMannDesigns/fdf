
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
	// maybe this process should be abstracted to a helper as we do it in 3 places now.
	draw->bg = mlx_new_image(draw->mlx, WIDTH, HEIGHT); // can mlx_new_image() fail? 
	mlx_image_to_window(draw->mlx, draw->bg, 0, 0); //draw image from top left corner
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			mlx_put_pixel(draw->bg, j++, i, BLACK);
		i++;
	}
	draw->img = mlx_new_image(draw->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(draw->mlx, draw->img, 0, 0); //draw image from top left corner
	return (TRUE);
}

/*
 * Sets default values for the image projection.
 * Scales image based on window size and initialises it in the centre.
 */
static void	set_initial_draw_values(t_fdf *fdf)
{
	// TODO figure out some math to centre the image in the window
	fdf->draw_values.x = (fdf->draw.img->width / 2) - (fdf->width * 20 / 3);
	fdf->draw_values.y = 20; 
	fdf->draw_values.width = 20;
	fdf->draw_values.z = 3;
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
	set_initial_draw_values(fdf);
	draw_wireframe(fdf);
	mlx_key_hook(fdf->draw.mlx, &key_events, (void *) fdf);
	mlx_loop(fdf->draw.mlx);
	mlx_terminate(fdf->draw.mlx);
	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
