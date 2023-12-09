
#include "fdf.h"

#define WIDTH 800
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
	int		i;
	uint32_t	colour;
	uint32_t	x_offset;
	uint32_t	y_offset;
	uint32_t	tile_width;
	uint32_t	tile_height;
	uint32_t	row;


	colour = 0XFFFF00FF;
	y_offset = 10;
	tile_width = img->width / fdf->width / 2;
	x_offset = (img->width / 2) - ((fdf->width * tile_width) / 2);
	tile_height = img->width / fdf->width / 3;
	
	printf("width = %d | height = %d | offset = %d\n", tile_width, tile_height, x_offset);
//	row = column = 0;
	i = x = y = row = 0;
	current = fdf->coord_list;
	while (current)
	{
		if (i >= fdf->width)
		{
			x = 0;
			i = 0;
			row++;
			y = row * tile_height;
			x_offset -= (tile_width / 2);
		}
		mlx_put_pixel(img, x_offset + x, y_offset + y, colour);
		x += tile_width;
		y += tile_height;	
		i++;
		current = current->next;
	}
	//mlx_loop_hook(fdf->mlx, hooksu, fdf->mlx);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);

	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
