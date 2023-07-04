/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:09:55 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/21 12:20:17 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	if (str[count] == '\n')
		count++;
	return (count);
}

int	ft_check_next_line(char *str)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (count == 1)
			str[j++] = str[i];
		if (str[i] == '\n')
			count = 1;
		str[i++] = 0;
	}
	return (count);
}

char	*make_line(char *buff, char *line)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	temp = malloc(sizeof(char) * (ft_strlen(buff) + ft_strlen(line) + 1));
	while (buff && buff[i])
	{
		temp[i] = buff[i];
		i++;
	}
	j = 0;
	while (line[j])
	{
		temp[i++] = line[j];
		if (line[j++] == '\n')
			break ;
	}
	temp[i] = '\0';
	free(buff);
	return (temp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*new_string;

	new_string = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!new_string)
		return (NULL);
	str = new_string;
	while (*s1)
		*new_string++ = *s1++;
	while (*s2)
		*new_string++ = *s2++;
	*new_string = '\0';
	return (str);
}
