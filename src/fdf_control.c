
#include "fdf.h"

// TODO re-implement RETURN_SUCCESS/ERROR as EXIT_SUCCESS/FAILURE ??

/**
 * This is where we set up the window, mlx image and scale of the wireframe
 * we draw into it.
 */
static int	draw_setup(t_fdf *fdf, t_draw *draw)
{
	// TODO check neither WIDTH nor HEIGHT exceed int_max, or some arbitrary lower value,
	// e.g. something reasonable given the dimensions of modern monitors
	ft_bzero((void *) draw, sizeof(t_draw));
	draw->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!draw->mlx)
		return (FALSE); // Error handling for mlx42 needed	
	draw->img = mlx_new_image(draw->mlx, WIDTH, HEIGHT);
	int i, j;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(
				draw->img,
				(uint32_t) j,
				(uint32_t) i,
				0X000000FF
			);
			j++;
		}
		i++;
	}

	mlx_image_to_window(draw->mlx, draw->img, 0, 0); //draw image from top left corner
	// All of this below may not be necessary
	// This was put in place to ensure the image was drawn in the 
	// centre of the window before the projection algo was determined
	draw->y_offset = 10; 
	draw->tile_width = draw->img->width / fdf->width ;
	draw->x_offset = draw->img->width / 1.5;
	draw->x_offset -= (fdf->width * draw->tile_width) / 2;
	draw->z_factor = 3;
	return (TRUE);
}

/*
 * The x,y,z coords from the next node are taken to give us the end point of
 * the horizontal line. The exception being when we get to the end of the row
 * which is checked at the start of the function.
 */
static int	find_next_point_across(t_draw *draw, t_coord *current)
{
	t_coord	*next;

	next = current->next;
	if (next->x == 0)
		return (FALSE);
	draw->x1 = next->x;
	draw->y1 = next->y;
	draw->z1 = next->z;
	return (TRUE);
}

/*
 * For each point, we also draw down to the point at the same x axis but on the
 * y axis + 1. This means we need to loop forward in coord nodes by the width
 * of the image. A flag has been added to optimise the final row. We no longer
 * need to draw down to the next row once we have reached the final row.
 */
static int	find_next_point_down(t_draw *draw, t_coord *current, int width)
{
	t_coord	*next;
	int	i;

	if (draw->last_row)
		return (FALSE);
	i = 0;
	next = current;
	while (i < width)
	{
		next = next->next;
		if (!next)
		{
			draw->last_row = TRUE;
			return (FALSE);
		}
		i++;
	} 
	draw->x1 = next->x; 
	draw->y1 = next->y;
	draw->z1 = next->z;
	return (TRUE);
}

/*
 * Takes x,y,z values of the current coord. Sets 'current' flag in the draw
 * struct to ensure projection calcs are only completed on its values once.
 */
static void	set_current_point(t_draw *draw, t_coord *current)
{
	draw->current = TRUE;
	draw->x0 = current->x;
	draw->y0 = current->y;
	draw->z0 = current->z;
	return ;
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");
	(void) param;
}

/*
 * Control loop which handles the drawing of the image. This is 'where the
 * magic happens'. We loop through the coord list, at each point mapping out
 * the next coordinate across and down, and plotting lines between them,
 * until we reach the end of the image.
 */
void	fdf_control(t_fdf *fdf)
{	
	t_coord	*current;
	t_draw	draw;

	if (!draw_setup(fdf, &draw))
		return ;	
	mlx_key_hook(draw.mlx, &my_keyhook, NULL);
	current = fdf->coord_list;
	while (current->next)
	{
		set_current_point(&draw, current);
		if (find_next_point_across(&draw, current))
			plot_line(&draw);
		if (find_next_point_down(&draw, current, fdf->width))
			plot_line(&draw);	
		current = current->next;
	}
	mlx_loop(draw.mlx);
	mlx_terminate(draw.mlx);
	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
