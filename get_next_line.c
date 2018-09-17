/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/16 23:55:42 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*fill_return(int length, int start, char buffer[])
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * length);
	while (i < length)
	{
		result[i] = buffer[start + i];
		i++;
	}
	return (result);
}

int			get_length_till_newline(char buf[], int start)
{
	int i;

	i = start;
	while (buf[start])
	{
		if (buf[start] == '\n' || buf[start] == 26)
			return (start - i + 1);
		start++;
	}
	return (-1);
}

int			get_next_line(const int fd, char **line)
{
	static int		start = 0;
	char			*result;
	int				newline;
	int				length;
	char			buffer[BUFF_SIZE];

	newline = 0;
	while (read(fd, &buffer, BUFF_SIZE) > 0 && newline == 0)
	{
		length = get_length_till_newline(buffer, start); 
		result = ft_strjoin(result, fill_return(length - 1, start, buffer));
		start += length;
		if (length > 0)
		{
			newline = 1;
			break;
		}
	}
	if (newline == 0)
		return (-1);
	if (*line != NULL)
		free(*line);
	*line = result;
	return (1);
}
