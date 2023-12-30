/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:52:23 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 15:16:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!new_image(draw->mlx, &(draw->bg)))
		return (FALSE);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			mlx_put_pixel(draw->bg, j++, i, BLACK);
		i++;
	}
	if (!new_image(draw->mlx, &(draw->img)))
		return (FALSE);
	return (TRUE);
}

/*
 * Sets default values for the image projection.
 * Scales image based on window size and initialises it in the centre.
 */
static void	set_initial_draw_values(t_fdf *fdf)
{
	// TODO figure out some math to centre the image in the window
	// Find the width of the image at its widest point
	// Find the height of the image at its highest point
	// With those values, we can think of the image as having a rectangular box around it
	// The box can be placed in the centre of the screen, based on its dimensions.

	// number of rows and columns of 'squares' in the image are
	// height - 1 and width - 1 repsectively
	//

	/* formula from SO post...
	 * W = U*(Nr+Nc)*sqrt(3)/2
	 * H = U*(Nr+Nc)/2
	 */
	int w, h, u, nr, nc;

	u = 20; //20px ...although this should scale down to a min value for huge maps
	nc = fdf->width;
	nr = fdf->height;

	w = (u * (nr + nc) * ROOT_3 / 2) / 2;
	h = (u * (nr + nc) / 2) / 2;

	printf("w = %d, h = %d, x = %d\n", w, h, (int) (COS_30 * u * fdf->height));

	fdf->draw_values.x = WIDTH / 2 - w + (int) (COS_30 * u * fdf->height);
	fdf->draw_values.y = HEIGHT / 2 - h; 
	fdf->draw_values.width = 20;
	fdf->draw_values.z = 1;
	fdf->draw.orig_width = 20;
	return ;
}

/*
 * Control function which handles the setup of the mlx functionality.
 * Here we create our window and call our hooks.
 * We set some initial default values to center the fdf image in the window.
 * We also call the draw function which handles the creation of the
 * wireframe image itself.
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
