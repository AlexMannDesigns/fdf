/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:21:34 by amann             #+#    #+#             */
/*   Updated: 2022/09/19 16:14:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	remove_string_loop(char **orig, size_t idx, char ***res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (orig[i])
	{
		if (i == (int) idx)
		{
			j++;
			idx = -1;
		}
		else
		{
			(*res)[i] = orig[j];
			i++;
			j++;
		}
	}
}

void	ft_remove_from_array(char ***orig, size_t idx)
{
	char	**res;
	size_t	len;

	len = ft_array_len(*orig);
	if (len > 1)
	{
		res = (char **) ft_memalloc(sizeof(char *) * len);
		if (!res)
			return ;
		remove_string_loop(*orig, idx, &res);
		ft_strdel(&((*orig)[idx]));
		free(*orig);
		*orig = res;
	}
	else
	{
		ft_strdel(&(*orig)[0]);
		free(*orig);
		*orig = NULL;
	}
}
