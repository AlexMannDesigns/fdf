
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
	draw->y_offset = 10; //make this more scalable
	draw->tile_width = draw->img->width / fdf->width / 2;
	draw->x_offset = (draw->img->width / 2);
	draw->x_offset -= ((fdf->width * draw->tile_width) / 2);
	draw->tile_height = draw->img->width / fdf->width / 3;
	return (TRUE);
}

/**
 * Every time we reach the end of a row (x-axis), we have to reset
 * x0 and i to zero and increment the row count.
 * The x_offset (i.e. the point the drawing starts), is slightly decremented
 * in order to create the isometric layout.
 * The 'angle' of the projection is determined by the distance between the rows
 * and x_offset.
 */
static void	newline_configure(t_draw *draw, int *i)
{
	draw->x0 = 0;
	*i = 0;
	(draw->row)++;
	draw->y0 = draw->row * draw->tile_height;
	draw->x_offset -= (draw->tile_width / 2);
	return ;
}

/**
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
	draw->x0 = draw->x_offset + (draw->tile_width * current->x);
	draw->y0 += draw->tile_height;
	if (next->x == 0)
		draw->end_of_row = TRUE;
	else
	{
		draw->end_of_row = FALSE;
		draw->x1 = draw->x_offset + (draw->tile_width * next->x);
		draw->y1 = draw->y0 + draw->tile_height;
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
	draw->x1 = (draw->tile_width * next->x) - (draw->tile_width / 2);
	draw->x1 += draw->x_offset;
	draw->y1 = draw->y0 + draw->tile_height;
	return ;
}

void	fdf_control(t_fdf *fdf)
{	
	t_coord	*current;
	t_draw	draw;
	int	i;

	if (!draw_setup(fdf, &draw))
		return ;	
	i = 0;
	current = fdf->coord_list;
	while (current)
	{
		if (i == fdf->width)
			newline_configure(&draw, &i);
		find_next_point_across(&draw, current);
		plot_line(&draw, FALSE);
		find_next_point_down(&draw, current, fdf->width);
		plot_line(&draw, TRUE);	
		i++;
		current = current->next;
	}
	mlx_loop(draw.mlx);
	mlx_terminate(draw.mlx);
	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
