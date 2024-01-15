/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:56:14 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 14:30:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static void	re_draw_image(t_fdf *fdf)
{
	mlx_delete_image(fdf->draw.mlx, fdf->draw.img);
	if (!new_image(fdf->draw.mlx, &(fdf->draw.img)))
	{
		mlx_terminate(fdf->draw.mlx);
		exit(EXIT_FAILURE);
	}
	draw_wireframe(fdf);
	return ;
}

static void	move_image_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	// on second thoughts, maybe we could simplify this process
	// Rather than doing complicated calculations we could probably
	// just add a check which makes sure pixels are actually being
	// plotted.


	int	img_h;
	int	img_w;
	int	h_edge_len;
	int	w_edge_len;

	img_h = get_actual_height(
		fdf->draw.tile_width, fdf->height, fdf->width
	);
	img_w = get_actual_width(
		fdf->draw.tile_width, fdf->height, fdf->width
	);
	h_edge_len = COS_30 * fdf->draw.tile_width * fdf->height;
	w_edge_len = SIN_30 * fdf->draw.tile_width * (fdf->width - 1);
	if (keydata.key == MLX_KEY_RIGHT
		&& fdf->draw_values.x < WIDTH + h_edge_len)
		fdf->draw_values.x += 10;
	else if (keydata.key == MLX_KEY_LEFT
		&& fdf->draw_values.x > w_edge_len - img_w)
		fdf->draw_values.x -= 10;
	else if (keydata.key == MLX_KEY_DOWN && fdf->draw_values.y < HEIGHT)
		fdf->draw_values.y += 10;
	else if (keydata.key == MLX_KEY_UP && fdf->draw_values.y > 0 - img_h)
		fdf->draw_values.y -= 10;
	return ;
}

static void	scale_image_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	int	scale;

	if (keydata.key == MLX_KEY_EQUAL)
	{
		scale = fdf->draw_values.width * 0.1;
		if (scale == 0)
			scale = 1;
		fdf->draw_values.width += scale;
	}
	else if (keydata.key == MLX_KEY_MINUS)
	{
		fdf->draw_values.width *= 0.9;
		if (fdf->draw_values.width == 0)
			fdf->draw_values.width = 1;
	}
	return ;
}

static int	find_add_coord(t_coord *orig, t_coord **new, t_rot *rotate)
{
	(void) orig;
	(void) new;
	(void) rotate;
	// loop forward by (width * j) + i in orig.
	// add that node to the end of the new list.
	return (TRUE);
}

static void	zero_to_ninety(t_fdf *fdf)
{
	// rotate struct needed...
	//int	temp, w, h, i, j;
	t_rot	rotate;
	t_coord	*new;

	new = NULL;
	rotate.h = fdf->height;
	rotate.w = fdf->width;
	rotate.i = 0;
	while (rotate.i < rotate.w)
	{
		rotate.j = rotate.h;
		while (rotate.j >= 0)
		{
			// loop to node at column 'i', row 'j' and add to new list
			// e.g. first node should be column 0, last row.
			if (find_add_coord(fdf->coord_list, &new, &rotate))
				return ; // handle malloc error
			(rotate.j)--;
		}
		(rotate.i)++;
	}
	// after 90 deg rotation, height and width values are swapped.
	rotate.temp = fdf->width;
	fdf->width = fdf->height;
	fdf->height = rotate.temp;
	return ;
}

static void	back_to_zero(t_fdf *fdf)
{
	fdf->rotate_angle = 0;
	return ;
}

void	rotate_ninety_degrees(t_fdf *fdf)
{
	fdf->rotate_angle += 90;
	if (fdf->rotate_angle == 90)
		zero_to_ninety(fdf);
	if (fdf->rotate_angle == 360)
		back_to_zero(fdf);
	return ;
}

static void	modify_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_J)
		fdf->draw_values.z -= 1;
	else if (keydata.key == MLX_KEY_K)
		fdf->draw_values.z += 1;
	else if (keydata.key == MLX_KEY_R)
		rotate_ninety_degrees(fdf);
	return ;
}

void	key_events(mlx_key_data_t keydata, void *fdf_ptr)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) fdf_ptr;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		move_image_event(fdf, keydata);
	else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		scale_image_event(fdf, keydata);
	else if (keydata.key == MLX_KEY_J || keydata.key == MLX_KEY_K)
		modify_event(fdf, keydata);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(fdf->draw.mlx);
		exit(EXIT_SUCCESS);
	}
	re_draw_image(fdf);
	return ;
}
