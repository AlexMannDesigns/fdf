
#include "fdf.h"

#define WIDTH 256
#define HEIGHT 256

// TODO re-implement RETURN_SUCCESS/ERROR as EXIT_SUCCESS/FAILURE ??
void	fdf_control(t_fdf *fdf)
{
	mlx_image_t	*img;
	
	// open window
	// define behaviour before start-up
	//mlx_set_setting(MLX_MAXIMIZED, true);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!fdf->mlx)
		return ; // Error handling for mlx42 needed	
	
	img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, img, 0, 0);
	mlx_put_pixel(img, 0, 0, 1); //0xFF0000FF);
	mlx_loop(fdf->mlx);
	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
