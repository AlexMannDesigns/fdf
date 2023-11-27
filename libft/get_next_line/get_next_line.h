/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:26:23 by amann             #+#    #+#             */
/*   Updated: 2022/07/25 14:39:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 8

# define TRUE 1
# define FALSE 0

typedef struct s_gnl
{
	char	*line;
	size_t	len;
	ssize_t	bytes_read;
	int	nl;
}		t_gnl;

char	*get_next_line(const int fd);

#endif
