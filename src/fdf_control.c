
#include "fdf.h"

#define WIDTH 256
#define HEIGHT 256
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
	t_coord		*next_x;
	t_coord		*next_y;
	uint32_t	c_x;
	uint32_t	n_x;
	uint32_t	c_y;
	uint32_t	n_y;
	uint32_t	x;
	uint32_t	colour;
	uint32_t	offset;

	int i;
	colour = 0XFFFF00FF;
	offset = img->width / fdf->width / 2;
	current = fdf->coord_list;	
	while (current->next)
	{
		next_x = current->next;
		
		c_x = offset + current->x * (img->width / fdf->width);
		c_y = offset + current->y * (img->height / fdf->width);
		n_x = offset + next_x->x * (img->width / fdf->width);
		x = c_x;
		while (c_x < n_x)
			mlx_put_pixel(img, c_x++, c_y, colour);
		next_y = current;
		i = 0;	
		while (i < fdf->width && next_y)
		{
			next_y = next_y->next;
			i++;
		}
		if (next_y)
			n_y = offset + next_y->y * (img->height / fdf->width);
		while (next_y && c_y < n_y)
			mlx_put_pixel(img, x, c_y++, colour);
		current = current->next;
	}
	//mlx_loop_hook(fdf->mlx, hooksu, fdf->mlx);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);

	fdf->exit_status = RETURN_SUCCESS;
	return ;
}
