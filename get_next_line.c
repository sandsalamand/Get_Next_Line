/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/19 01:41:50 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		unsf_strlen(const char *str)
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

	str1len = unsf_strlen(s1);
	str2len = unsf_strlen(s2);
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
	//should probably free the two strings here, will save that for when there are less major bugs to fix
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
	while (i < BUFF_SIZE)
	{
		if (buf[i] == '\n' || buf[i] == 26)
			return(i - start + 1);
		i++;
	}
	return (-1);
}

int			buff_revsearch(char buff[BUFF_SIZE], char c)
{
	int	strlen;
	int i;
	
	i = 0;
	strlen = BUFF_SIZE - 1;
	while (strlen >= 0)
	{
		if (buff[strlen] == c)
			return (i);
		i++;
		strlen--;
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
		{
			length = buff_revsearch(last_buffer, '\n');
			if (BUFF_SIZE - length != last_len)
			{
				//need to be able to differentiate here if there's like 5 newlines in one buffer, need a better method
				//might just rewrite the whole thing to be more robust and need less if statements
				if (get_length_till_newline(last_buffer, last_len) != BUFF_SIZE - length)
				{
					*line = fill_return(last_len, get_length_till_newline(last_buffer, last_len), last_buffer);
					break;
				}
			}
		}
		newline = 2;
		length = get_length_till_newline(buffer, 0);
		if (length == -1)
			*line = unsf_strjoin(*line, fill_return(0, BUFF_SIZE, buffer));
		else if (length > 0)
		{
			*line = unsf_strjoin(*line, fill_return(0, length - 1, buffer));
			last_len = length;
			newline = 1;
			copy_buffer(last_buffer, buffer);
			break;
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
