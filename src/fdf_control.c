
#include "fdf.h"

// TODO re-implement RETURN_SUCCESS/ERROR as EXIT_SUCCESS/FAILURE ??
// TODO make draw_setup better (see comment)

/**
 * This is where we set up the window, mlx image and scale of the wireframe
 * we draw into it.
 * At the moment, each 'square' of the grid is scaled based on the width
 * of the mlx image. This is to prevent attempting to draw outside of it
 * and causing a crash (i.e. put_pixel outside to coords outside of img
 * boundaries). We could implement better error handling to allow more
 * flexibility and user control here...
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
	mlx_image_to_window(draw->mlx, draw->img, 0, 0); //draw image from top left corner
	// All of this below may not be necessary
	// This was put in place to ensure the image was drawn in the 
	// centre of the window before the projection algo was determined
	draw->y_offset = 10; 
	draw->tile_width = draw->img->width / fdf->width / 1.5;
	draw->x_offset = (draw->img->width / 1.5);
	draw->x_offset -= ((fdf->width * draw->tile_width) / 2);
	draw->z_factor = 5;
	return (TRUE);
}

static int	find_next_point_across(t_draw *draw, t_coord *current)
{
	t_coord	*next;

	next = current->next;
	if (next->x == 0)
		return (FALSE);
	draw->x1 = next->x;
	draw->y1 = next->y;
	draw->z1 = next->z;
	projection_control(draw, &(draw->x1), &(draw->y1), &(draw->z1));
	return (TRUE);
}

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
	projection_control(draw, &(draw->x1), &(draw->y1), &(draw->z1));
	return (TRUE);
}


static int	set_current_point(t_draw *draw, t_coord *current)
{
	if (current->next == NULL)
		return (FALSE);
	draw->x0 = current->x;
	draw->y0 = current->y;
	draw->z0 = current->z;
	projection_control(draw, &(draw->x0), &(draw->y0), &(draw->z0));
	return (TRUE);
}

void	fdf_control(t_fdf *fdf)
{	
	t_coord	*current;
	t_draw	draw;

	if (!draw_setup(fdf, &draw))
		return ;	
	current = fdf->coord_list;
	// this loop is a bit of a mess. We should find a way of doing this
	// without having to pass around booleans.
	while (TRUE)
	{
		if (!set_current_point(&draw, current))
			break ;
		
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
