/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:06:31 by amann             #+#    #+#             */
/*   Updated: 2024/02/10 16:24:17 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Here, we handle the buff after copying to line.
 * len represents the length of what was copied from it. So, if there is a nl
 * char at this index, we need to copy what is after that char into a temp
 * var, bzero the buff then copy back to the start of the buff.
 * Otherwise, we know all of the buff was copied, so we can just bzero the
 * whole thing again.
 * We must also ensure the size of len is updated to represent how much can
 * be read into the buff during the next read() call.
 */
static void	update_buff(t_gnl *gnl, char *buff)
{
	char	temp_buff[BUFF_SIZE + 1];

	if (buff[gnl->len] == '\n')
	{
		gnl->nl = TRUE;
		ft_strcpy(temp_buff, buff + (gnl->len + 1));
		ft_bzero((void *) buff, BUFF_SIZE);
		ft_strcpy(buff, temp_buff);
	}
	else
	{
		ft_bzero((void *) buff, BUFF_SIZE);
		gnl->len = 0;
	}
	return ;
}

/*
 * When some text is successfully read into the buff, we need to start copying
 * to our line var using heap memory.
 * First, we read through the buff, copying each char to a temp var until we
 * hit a new line or the end of the buff.
 * If line has not yet been allocated, we just strdup the temp var into it.
 * Otherwise, we copy the existing line into another temp var, free it, then
 * strjoin the two temp vars together to make a new line.
 */
static int	dup_to_nl(t_gnl *gnl, char *buff)
{
	char	*temp_line;
	char	new_line[BUFF_SIZE + 1];

	gnl->len = 0;
	while (buff[gnl->len] && buff[gnl->len] != '\n')
	{
		new_line[gnl->len] = buff[gnl->len];
		(gnl->len)++;
	}
	new_line[gnl->len] = '\0';
	if (!(gnl->line))
		gnl->line = ft_strdup(new_line);
	else
	{
		temp_line = ft_strjoin(gnl->line, new_line);
		free(gnl->line);
		gnl->line = temp_line;
	}
	if (!(gnl->line))
		return (FALSE);
	update_buff(gnl, buff);
	return (TRUE);
}

/*
 * Wrapper around the read call, handling the varying relative buff sizes.
 */
static void	gnl_read(t_gnl *gnl, int fd, char *buff)
{
	void	*read_ptr;
	size_t	n_bytes;

	read_ptr = (void *)(buff + gnl->len);
	n_bytes = (size_t)(BUFF_SIZE - gnl->len);
	gnl->r_ret = read(fd, read_ptr, n_bytes);
	return ;
}

/*
 * Initial set-up for get_next_line. Zeroes-out the struct and handles any
 * existing nl char in the buff from previous reads. If so, FALSE can be
 * returned to ensure an immediate exit. Otherwise, we return TRUE and enter
 * the read loop. Also, fd's higher than MAX_FD are dismissed.
 */
static int	gnl_setup(t_gnl *gnl, int fd, char *buff)
{
	ft_bzero((void *) gnl, sizeof(t_gnl));
	if (fd >= MAX_FD)
		return (FALSE);
	if (ft_strchr(buff, '\n'))
	{
		dup_to_nl(gnl, buff);
		return (FALSE);
	}
	gnl->len = ft_strlen(buff);
	return (TRUE);
}

/*
 * Returns either the read line or null in the event of an error or nothing
 * else to read
 * Should be able to read from stdin
 */
char	*get_next_line(const int fd)
{
	static char	buff[MAX_FD][BUFF_SIZE + 1];
	t_gnl		gnl;

	if (!gnl_setup(&gnl, fd, buff[fd]))
		return (gnl.line);
	gnl_read(&gnl, fd, buff[fd]);
	while (gnl.r_ret)
	{
		if (gnl.r_ret == -1)
		{
			free(gnl.line);
			return (NULL);
		}
		if (!dup_to_nl(&gnl, buff[fd]))
			return (NULL);
		if (gnl.nl)
			return (gnl.line);
		gnl_read(&gnl, fd, buff[fd]);
	}
	if (!ft_strlen(buff[fd]))
		return (NULL);
	dup_to_nl(&gnl, buff[fd]);
	return (gnl.line);
}
