
#include "fdf.h"

// TODO re-implement RETURN_SUCCESS/ERROR as EXIT_SUCCESS/FAILURE ??

/*
static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	hooksu(void *param)
{
	const mlx_t	*mlx;

	mlx = param;
	printf("WIDTH: %d | HEIGHT: %d | COLOUR: %0#10x\n",
		mlx->width,
		mlx->height,
		get_rgba(255, 0, 0, 255));
}
*/
static int	draw_setup(t_fdf *fdf, t_draw *draw)
{
	ft_bzero((void *) draw, sizeof(t_draw));
	draw->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!draw->mlx)
		return (FALSE); // Error handling for mlx42 needed	
	draw->img = mlx_new_image(draw->mlx, WIDTH, HEIGHT);
	//ft_memset(img->pixels, 0x00, img->width * img->height * BPP);
	mlx_image_to_window(draw->mlx, draw->img, 0, 0); //draw image from top left corner
	draw->y_offset = 10; //make this more scalable
	draw->tile_width = draw->img->width / fdf->width / 2;
	draw->x_offset = (draw->img->width / 2) - ((fdf->width * draw->tile_width) / 2);
	draw->tile_height = draw->img->width / fdf->width / 3;
	return (TRUE);
}

static void	newline_configure(t_draw *draw, int *i)
{
	draw->x0 = 0;
	*i = 0;
	(draw->row)++;
	draw->y0 = draw->row * draw->tile_height;
	draw->x_offset -= (draw->tile_width / 2);
	return ;
}

	/*
	printf("x0 %d y0 %d | x1 %d y1 %d | dx %d dy %d\n",
		x,
		y,
		draw->x1,
		draw->y1,
		dx,
		dy
	);*/
static void	find_next_point_across(t_draw *draw, t_coord *current)
{
	// check next is not NULL
	// check x value of next node.
	// if next x < current x then we are at the end of the row
	//	- this should not happen due to if check in fdf_control loop
	//
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
	draw->x1 = draw->x_offset + (draw->tile_width * next->x) - (draw->tile_width / 2);
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
