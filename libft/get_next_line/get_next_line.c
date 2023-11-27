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

#include <stdio.h>

static int	dup_to_nl(t_gnl *gnl, char *buff);

/*
 * After read returns 0 we need to copy across any remaining contents from the
 * buff or return NULL
 */
static char	*wrap_up(t_gnl *gnl, char *buff)
{
	if (!ft_strlen(buff))
		return (NULL);
	dup_to_nl(gnl, buff);
	return (gnl->line);
}

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
 * Returns either the read line or null in the event of an error or nothing 
 * else to read
 * Should be able to read from stdin
 * TODO more testing needed - large buffs infinite loop, small buffs crash 
 */
char	*get_next_line(const int fd)
{
	static char	buff[BUFF_SIZE + 1];
	t_gnl		gnl;
	
	ft_bzero((void *) &gnl, sizeof(t_gnl));
	if (ft_strchr(buff, '\n') && !dup_to_nl(&gnl, buff))
		return (NULL);
	if (gnl.nl)
		return (gnl.line);
	gnl.len = ft_strlen(buff);
	gnl.r_ret = read(fd, (void *) (buff + gnl.len), BUFF_SIZE - gnl.len);
	while (gnl.r_ret)
	{
		if (gnl.r_ret == -1) // read error
		{
			free(gnl.line);
			return (NULL);
		}
		if (!dup_to_nl(&gnl, buff))
			return (NULL);
		if (gnl.nl)
			return (gnl.line);
		gnl.r_ret = read(fd, (void *) (buff + gnl.len) , BUFF_SIZE - gnl.len);
	}
	return (wrap_up(&gnl, buff));
}
