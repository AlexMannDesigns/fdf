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

static size_t	get_buff_len(char **buff)
{
	if (*buff)
		return (ft_strlen(*buff));
	ft_bzero((void *) *buff, BUFF_SIZE + 1);
	return (0);
}

/*
	if (!line)
		return (NULL);
	if ((*buff)[len] == '\n')
	{
		ft_strcpy(temp_buff, *buff + len);
		ft_bzero((void *) *buff, BUFF_SIZE);
		ft_strcpy(*buff, temp_buff);	
	}
	else
		ft_bzero((void *) *buff, BUFF_SIZE);
	return (line);
*/

static void	dup_to_nl(char **line, char **buff)
{
	size_t	len;
	char	temp_line[BUFF_SIZE];
	char	new_line[BUFF_SIZE];
	char	temp_buff[BUFF_SIZE];

	ft_bzero((void *) new_line, BUFF_SIZE);
	len = 0;
	while ((*buff)[len] && (*buff)[len] != '\n')
	{
		new_line[len] = (*buff)[len];
		len++;
	}
	if (!(*line))
		*line = ft_strdup(new_line);
	else
	{
		ft_strcpy(temp_line, *line);
		free(*line);
		*line = ft_strjoin(temp_line, new_line);
	}
	return ;
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
	
	line = NULL;
	bytes_read = read(fd, (void *) (buff + get_buff_len(&buff)), BUFF_SIZE);
	while (bytes_read)
	{
		if (bytes_read == -1 || bytes_read < BUFF_SIZE)
			return (NULL);
		dup_to_nl(&line, &buff); // No malloc prot needed - will return NULL either way
		bytes_read = read(fd, (void *) buff, BUFF_SIZE);
	}
	// if (bytes_read == 0) end of file?
	//	return (line);
	return (line);
}
