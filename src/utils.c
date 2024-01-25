/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:03:15 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 14:04:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

/*
 * Frees any heap-allocated memory and then returns the exit value
 */
int	free_and_exit(t_fdf *fdf)
{
	t_coord	*coord;
	t_coord	*next;

	coord = fdf->coord_list;
	if (!coord)
	{
		return (fdf->exit_status);
	}
	while (coord)
	{
		next = coord->next;
		ft_memdel((void **)&coord);
		coord = next;
	}
	return (fdf->exit_status);
}

/*
 * All-purpose error message printer
 * Prints 'msg' to STDERR, followed by NL, and then returns 'ret'
 */
int	print_error(int ret, char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (ret);
}
