/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:06:31 by amann             #+#    #+#             */
/*   Updated: 2022/07/15 16:36:29 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* In case of errors, we free the malloc'd pointer and return NULL */
static char	*free_return_null(char **line)
{
	ft_strdel(line);
	return (NULL);
}

static char	*find_newline(char *buff)
{
	

}

/*
 * Returns either the read line or null in the event of an error or nothing 
 * else to read
 * Should be able to read from stdin 
 */
char	*get_next_line(const int fd)
{
	static char	buff[BUFF_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;
	
	ft_bzero((void *) buff, BUFF_SIZE + 1);
	bytes_read = read(fd, (void *) buff, BUFF_SIZE);
	while (bytes_read)
	{
		if (bytes_read == -1 || bytes_read < BUFF_SIZE)
			return (free_return_null(&line));
		line = find_newline(buff);
		if (!line)
			return (NULL);
		if (ft_strchr(line, '\n'))
			break ;
		ft_bzero((void *) buff, BUFF_SIZE + 1);
		bytes_read = read(fd, (void *) buff, BUFF_SIZE);
	}
	// if (bytes_read == 0) end of file?
	//	return (line);
	return (line);
}
