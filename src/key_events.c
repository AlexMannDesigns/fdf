/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:56:14 by amann             #+#    #+#             */
/*   Updated: 2024/02/10 14:21:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static void	move_image_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_RIGHT)
	{
		fdf->draw_values.x += 10;
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		fdf->draw_values.x -= 10;
	}
	else if (keydata.key == MLX_KEY_DOWN)
	{
		fdf->draw_values.y += 10;
	}
	else if (keydata.key == MLX_KEY_UP)
	{
		fdf->draw_values.y -= 10;
	}
	return ;
}

static void	scale_image_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	int	scale;

	if (keydata.key == MLX_KEY_EQUAL)
	{
		scale = fdf->draw_values.width * 0.1;
		if (scale == 0)
		{
			scale = 1;
		}
		fdf->draw_values.width += scale;
	}
	else if (keydata.key == MLX_KEY_MINUS)
	{
		fdf->draw_values.width *= 0.9;
		if (fdf->draw_values.width == 0)
		{
			fdf->draw_values.width = 1;
		}
	}
	return ;
}

static void	modify_event(t_fdf *fdf, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_J)
	{
		fdf->draw_values.z -= 1;
	}
	else if (keydata.key == MLX_KEY_K)
	{
		fdf->draw_values.z += 1;
	}
	return ;
}

static void	handle_keys(t_fdf *fdf, mlx_key_data_t keydata)
{
	fdf->draw.img_visible = FALSE;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
	{
		move_image_event(fdf, keydata);
	}
	else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
	{
		scale_image_event(fdf, keydata);
	}
	else if (keydata.key == MLX_KEY_J || keydata.key == MLX_KEY_K)
	{
		modify_event(fdf, keydata);
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(fdf->draw.mlx);
		exit(EXIT_SUCCESS);
	}
	return ;
}

void	key_events(mlx_key_data_t keydata, void *fdf_ptr)
{
	t_fdf			*fdf;
	t_draw_values	orig;

	fdf = (t_fdf *) fdf_ptr;
	orig.x = fdf->draw_values.x;
	orig.y = fdf->draw_values.y;
	orig.z = fdf->draw_values.z;
	orig.width = fdf->draw_values.width;
	if (keydata.action != MLX_PRESS)
	{
		return ;
	}
	handle_keys(fdf, keydata);
	re_draw_image(fdf);
	if (!(fdf->draw.img_visible))
	{
		fdf->draw_values.x = orig.x;
		fdf->draw_values.y = orig.y;
		fdf->draw_values.z = orig.z;
		fdf->draw_values.width = orig.width;
		re_draw_image(fdf);
	}
	return ;
}
