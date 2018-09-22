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

int		getstr(int strt, int end, char buf[BUFF_SIZE], char **line)
{
	int i;
	char *str;

	ft_putstr("start: ");
	putnbr_endl(strt);
	ft_putstr("end: ");
	putnbr_endl(end);
	str = ft_strnew(end - strt);
	i = 0;
	while (strt <= end)
	{
		//ft_putchar(buf[strt]);
		str[i] = buf[strt];
		i++;
		strt++;
	}
	if (!(*line))
		*line = str;	
	*line = ft_strjoin(*line, str);
	free(str);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char		act_buf[BUFF_SIZE];
	static int		cur_byte = 0;
	int				strt_byte;
	int				buf_scanner;

	if (cur_byte == 0)
	{
		free(*line);
		if (read(fd, &act_buf, BUFF_SIZE) == 0)
			return (0);
	}
	strt_byte = cur_byte;
	buf_scanner = 0;
	while (act_buf[buf_scanner]) //OR == 26
	{
		if (act_buf[buf_scanner] == '\n' ||
			 act_buf[buf_scanner] == 26)
		{
			getstr(strt_byte, buf_scanner, act_buf, &(*line));
			buf_scanner++;
			cur_byte++;
			break;
		}
		buf_scanner++;
		cur_byte++;
		if (buf_scanner == BUFF_SIZE)
		{
			getstr(strt_byte, BUFF_SIZE - 1, act_buf, &(*line));
			buf_scanner = 0;
			if (read(fd, &act_buf, BUFF_SIZE) == 0)
				return (0);
		}
	}
	return (0);
}
