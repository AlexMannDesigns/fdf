
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
	draw->tile_width = draw->img->width / fdf->width / 1.2;
	draw->x_offset = (draw->img->width / 1.5);
	draw->x_offset -= ((fdf->width * draw->tile_width) / 2);
	draw->z_factor = 5;
	return (TRUE);
}

/**
 * Every time we reach the end of a row (x-axis), we have to reset
 * x0 and i to zero and increment the row count.
 * The x_offset (i.e. the point the drawing starts), is slightly decremented
 * in order to create the isometric layout.
 * The 'angle' of the projection is determined by the distance between the rows
 * and x_offset.

static void	newline_configure(t_draw *draw, int *i)
{
	draw->x0 = 0;
	*i = 0;
	(draw->row)++;
	draw->y0 = draw->row * draw->tile_height;
	draw->x_offset -= (draw->tile_width / 2);
	return ;
}*/

/*
 * Here we first check if we have reached the end of a row or final coord, as these
 * need to be handled differently. We do not need to draw across to the next point in 
 * this scenario. 
 * Otherwise, we are finding the current and next x&y coords from the list and adding
 * them to the draw struct.
 * The z axis essentially pulls the point up and to the left, provided it is positive.
 *
*/
static void	find_next_point_across(t_draw *draw, t_coord *current)
{
	t_coord	*next;

	next = current->next;
	if (!next)
	{
		draw->end_of_row = TRUE;
		return ;
	}
	// this should be done elsewhere...
	// How about we just find the current point at the start of each iteration?
	draw->x0 = current->x;
	draw->y0 = current->y;
	draw->z0 = current->z;
	if (next->x == 0)
		draw->end_of_row = TRUE;
	else
	{
		draw->end_of_row = FALSE;
		draw->x1 = next->x;
		draw->y1 = next->y;
		draw->z1 = next->z;
	}	
	return ;
}

/*
 * Finding the next point down is a little more tricky. We need to move by the
 * width of the image down the list. We have a last_row flag to optimise this
 * process slightly, as we do not need to draw down from any of the last row 
 * of coords.
 * We do not need to set x0 and y0 here as these will not have changed from
 * find_next_point_across().
*/
static void	find_next_point_down(t_draw *draw, t_coord *current, int width)
{
	t_coord	*next;
	int	i;

	if (draw->last_row)
		return ;
	i = 0;
	next = current;
	while (i < width)
	{
		next = next->next;
		if (!next)
		{
			draw->last_row = TRUE;
			return ;
		}
		i++;
	} 
	draw->x1 = next->x; 
	draw->y1 = next->y;
	draw->z1 = next->z;
	return ;
}

void	isometric_projection_test(t_draw *draw, int draw_across)
{
	int x;
	int y;
	int z;

	// Horrible code repetition here, please fix
	if (draw_across)
	{
		x = draw->x0 * draw->tile_width;
		y = draw->y0 * draw->tile_width;
		z = draw->z0 * draw->z_factor;
		draw->x0 = draw->x_offset + (int) ((x - y) * COS_30);
		draw->y0 = draw->y_offset + (int) (-z + (x + y) * SIN_30);
	}
	//printf("x = %d | y = %d\n", draw->x0, draw->y0);
	x = draw->x1 * draw->tile_width;
	y = draw->y1 * draw->tile_width;
	z = draw->z1 * draw->z_factor;	
	draw->x1 = draw->x_offset + (int) ((x - y) * COS_30);
	draw->y1 = draw->y_offset + (int) (-z + (x + y) * SIN_30);
	return ;
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
	while (current)
	{
		//set current point first...?
		// this is happening in find_next_point_across() then skipped in
		// find_next_point_down() -> might be more readable if it happens separately
		find_next_point_across(&draw, current);
		isometric_projection_test(&draw, TRUE);
		plot_line(&draw, FALSE);
		
		find_next_point_down(&draw, current, fdf->width);
		isometric_projection_test(&draw, FALSE);
		plot_line(&draw, TRUE);	
		
		current = current->next;
	}
	mlx_loop(draw.mlx);
	mlx_terminate(draw.mlx);
	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
