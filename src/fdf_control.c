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
#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

// TODO check neither WIDTH nor HEIGHT exceed int_max, or some arbitrary lower value,
// e.g. something reasonable given the dimensions of modern monitors

int	draw_background(t_draw *draw, uint32_t height, uint32_t width)
{
	uint32_t	i;
	uint32_t	j;

	if (!new_image(draw->mlx, &(draw->bg), *draw))
		return (FALSE);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
			draw_pixel(draw, draw->bg, j++, i, BLACK);
		i++;
	}
	return (TRUE);
}

/**
 * This is where we set up the window, and mlx background img.
 * The background image is set to black, pixel by pixel, when the program
 * starts. We then set up a new, transparent layer, which will be overlayed
 * on the background for the wireframe to be drawn on.
 */
int	mlx_setup(t_draw *draw)
{
	ft_bzero((void *) draw, sizeof(t_draw));
	draw->current_win_h = HEIGHT;
	draw->current_win_w = WIDTH;
	draw->mlx = mlx_init(draw->current_win_w, draw->current_win_h, "fdf", true);
	if (!draw->mlx)
		return (print_error(FALSE, ERROR_MLX));
	if (!draw_background(draw, draw->current_win_h, draw->current_win_w))
		return (FALSE);
	if (!new_image(draw->mlx, &(draw->img), *draw))
		return (print_error(FALSE, ERROR_MLX));
	return (TRUE);
}

/*
 * Sets default values for the image projection.
 * Scales image based on window size and initialises it in the centre.
 */
static void	set_initial_draw_values(t_fdf *fdf)
{
	int	w;
	int	h;
	int	u;

	u = 20;
	w = get_actual_width(u, fdf->height, fdf->width - 1);
	h = get_actual_height(u, fdf->height, fdf->width - 1);
	while ((w > WIDTH || h > HEIGHT) && u > 3)
	{
		u--;
		w = get_actual_width(u, fdf->height, fdf->width - 1);
		h = get_actual_height(u, fdf->height, fdf->width - 1);
	}
	fdf->draw_values.x = (WIDTH / 2) - (w / 2) + (int) (COS_30 * u * fdf->height);
	fdf->draw_values.y = (HEIGHT / 2) - (h / 2); 
	fdf->draw_values.width = u;
	fdf->draw_values.z = 1;
	fdf->draw.orig_width = u;
	return ;
}

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

/*
 * Control function which handles the setup of the mlx functionality.
 * Here we create our window and call our hooks.
 * We set some initial default values to center the fdf image in the window.
 * We also call the draw function which handles the creation of the
 * wireframe image itself.
 */
void	fdf_control(t_fdf *fdf)
{
	if (!fdf->coord_list) 
		return ((void) print_error(FALSE, ERROR_NO_VALUES));
	if (!mlx_setup(&(fdf->draw)))
		return ;
	set_initial_draw_values(fdf);
	draw_wireframe(fdf);

	mlx_resize_hook(fdf->draw.mlx, &resize_event, (void *) fdf);

	mlx_key_hook(fdf->draw.mlx, &key_events, (void *) fdf);
	mlx_loop(fdf->draw.mlx);
	mlx_terminate(fdf->draw.mlx);
	fdf->exit_status = EXIT_SUCCESS;
	return ;
}
