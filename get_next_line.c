/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/18 01:08:00 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		uns_strlen(const char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*unsf_strjoin(char const *s1, char const *s2)
{
	char		*result;
	size_t		str1len;
	size_t		str2len;
	size_t		i;

	str1len = uns_strlen(s1);
	str2len = uns_strlen(s2);
	result = (char*)malloc(sizeof(char) * (str1len + str2len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < str1len)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < str1len + str2len)
	{
		result[i] = s2[i - str1len];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char		*fill_return(int start_pos, int length, char buffer[])
{
	char	*result;
	int		i;
	int		z;

	result = malloc(sizeof(char) * length);
	z = 0;
	while (z < start_pos)
		z++;
	i = 0;
	while (i < length)
	{
		result[i] = buffer[z];
		i++;
		z++;
	}
	return (result);
}

int			get_length_till_newline(char buf[], int start)
{
	int i;

	i = start;
	while (start < i + BUFF_SIZE)
	{
		if (buf[start] == '\n' || buf[start] == 26)
			return (start - i + 1);
		start++;
	}
	return (-1);
}

void		copy_buffer(char dest[BUFF_SIZE], char source[BUFF_SIZE])
{
	int i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		dest[i] = source[i];
		i++;
	}
}

int			get_next_line(const int fd, char **line)
{
	static char		last_buffer[BUFF_SIZE];
	static int		current_line = 0;
	static int		last_len = 0;
	int				start = 0;
	int				newline;
	int				length;
	char			buffer[BUFF_SIZE];

	newline = 0;
	if (*line)
		ft_strdel(line);
	*line = ft_strnew(1);
	while (read(fd, &buffer, BUFF_SIZE) > 0 && newline != 1)
	{
		if (current_line > 0 && newline == 0)
			*line = fill_return(last_len, BUFF_SIZE - last_len, last_buffer);
		newline = 2;
		length = get_length_till_newline(buffer, start);
		if (length == -1)
		{
			*line = unsf_strjoin(*line, fill_return(0, BUFF_SIZE, buffer));
			start += BUFF_SIZE;
		}
		else if (length > 0)
		{
			*line = unsf_strjoin(*line, fill_return(0, length - 1, buffer));
			newline = 1;
			last_len = length;
			copy_buffer(last_buffer, buffer);
		}
		else if (length == 0)
		{
			ft_putendl("empty line");
		}
	}
	if (newline != 1)
		return (-1);
	current_line++;
	return (1);
}
