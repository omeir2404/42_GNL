/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:09:35 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/21 16:27:24 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (0);
	line = NULL;
	while (buff[fd][0] || read(fd, buff[fd], BUFFER_SIZE) > 0)
	{
		line = make_line(line, buff[fd]);
		if (ft_check_next_line(buff[fd]) == 1)
			break ;
		if (read(fd, buff[fd], BUFFER_SIZE) < 0)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
