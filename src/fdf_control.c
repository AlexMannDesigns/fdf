
#include "fdf.h"

#define WIDTH 512
#define HEIGHT 512
#define BPP sizeof(int32_t)

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
void	fdf_control(t_fdf *fdf)
{
	mlx_image_t	*img;
		
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!fdf->mlx)
		return ; // Error handling for mlx42 needed	
	img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	//ft_memset(img->pixels, 0x00, img->width * img->height * BPP);
	mlx_image_to_window(fdf->mlx, img, 0, 0);

	t_coord		*current;
	uint32_t	x;
	uint32_t	y;
	uint32_t	colour;
	uint32_t	x_offset;
	uint32_t	tile_width;
	uint32_t	tile_height;
	uint32_t	column;
	uint32_t	row;


	uint32_t i;
	colour = 0XFFFF00FF;
	tile_width = img->width / fdf->width / 2;
	x_offset = (img->width / 2) - tile_width;
	tile_height = img->height / fdf->width / 4;
	current = fdf->coord_list;
	row = column = 0;	
	while (current)
	{
		if (column > (uint32_t) fdf->width)
		{
			column = 0;
			row++;
		}
		x = (x_offset - (tile_width * column)) + (current->x * tile_width);
		y = (row * tile_height) + current->y + (tile_height * column);
		if (x < 0)
			break ;
		i = 0;
		while (i < tile_width)
		{
			printf("x = %3d | y = %3d | width = %3d\n", x, y, tile_width);
			mlx_put_pixel(img, x++, y++, colour);
			i++;
		}
		/*
		i = 0;	
		while (i < fdf->width && next_y)
		{
			next_y = next_y->next;
			i++;
		}
		if (next_y)
			n_y = next_y->y * (img->height / fdf->width / 4);
		while (next_y && y < n_y - ((n_y - y) / 2))
		{
			printf("x = %3d | y = %3d\n", x, y);
			mlx_put_pixel(img, x--, y++, colour);
		}
		*/
		column++;
		current = current->next;
	}
	//mlx_loop_hook(fdf->mlx, hooksu, fdf->mlx);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);

	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
