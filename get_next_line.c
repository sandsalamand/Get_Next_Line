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
#define PREV_LINES BUFF_SIZE * line_ct

int		getstr(int strt, int end, char buf[BUFF_SIZE], char **line)
{
	int i;
	char *str;

	ft_putstr("start: ");
	putnbr_endl(strt);
	ft_putstr("end: ");
	putnbr_endl(end);
	str = malloc(sizeof(char) * (end - strt));
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
	static int		line_ct = 0;
	int				strt_byte;

	if (cur_byte == 0)
	{
		free(*line);
		if (read(fd, &act_buf, BUFF_SIZE) == 0)
			return (0);
	}
	strt_byte = cur_byte;
	while (act_buf[cur_byte - (PREV_LINES)])
	{
		if (act_buf[cur_byte - (PREV_LINES)] == '\n' ||
			 act_buf[cur_byte - (PREV_LINES)] == 26)
		{
			getstr(strt_byte, cur_byte - (PREV_LINES), act_buf, &(*line));
			cur_byte++;
			line_ct++;
			break;
		}
		cur_byte++;
		if (cur_byte - (PREV_LINES) == BUFF_SIZE)
		{
			getstr(strt_byte, BUFF_SIZE - 1, act_buf, &(*line));
			if (read(fd, &act_buf, BUFF_SIZE) == 0)
				return (0);
			line_ct++;
		}
	}
	return (0);
}
