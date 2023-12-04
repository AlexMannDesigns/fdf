
#include "fdf.h"

#define WIDTH 256
#define HEIGHT 256
#define BPP sizeof(int32_t)

// TODO re-implement RETURN_SUCCESS/ERROR as EXIT_SUCCESS/FAILURE ??


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

void	fdf_control(t_fdf *fdf)
{
	mlx_image_t	*img;
		
	// open window
	// define behaviour before start-up
	//mlx_set_setting(MLX_MAXIMIZED, true);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!fdf->mlx)
		return ; // Error handling for mlx42 needed	
	
	
	img = mlx_new_image(fdf->mlx, 128, 128);

	// set every pixel in the image to a specific value	
	ft_memset(img->pixels, 0, img->width * img->height * BPP);
	
	mlx_image_to_window(fdf->mlx, img, 0, 0);

	uint32_t i = 0;
	while (i < img->height)
	{
		mlx_put_pixel(img, (img->width / 2), i, 0xFF0000FF);
		mlx_put_pixel(img, i, (img->height / 2), 0xFF0000FF);
		i++;
	}
	mlx_loop_hook(fdf->mlx, hooksu, fdf->mlx);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);

	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
