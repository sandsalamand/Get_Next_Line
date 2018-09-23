/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/23 00:00:17 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define PREV_LINES BUFF_SIZE * line_ct

int		getstr(int strt, int end, char buf[BUFF_SIZE], char **line)
{
	int i;
	char *str;

	str = ft_strnew(end - strt - 1);
	i = 0;
	while (strt <= end)
	{
		str[i] = buf[strt];
		i++;
		strt++;
	}
	if (!(*line))
		*line = str;	
	else
		*line = ft_strjoin(*line, str);
	free(str);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char		act_buf[BUFF_SIZE];
	static int		cur_byte = 0;
	static int		line_ct = 0;
	char			*buf;
	int				strt_byte;

	free(*line);
	*line = ft_strnew(1);
	if (cur_byte == 0)
	{
		if (read(fd, &act_buf, BUFF_SIZE) == 0)
			return (0);
	}
	strt_byte = cur_byte;
	buf = ft_strnew((BUFF_SIZE * (line_ct + 1)) - 1);
	while (act_buf[cur_byte - (PREV_LINES)])
	{
		buf[cur_byte - (PREV_LINES)] = act_buf[cur_byte - (PREV_LINES)];
		if (act_buf[cur_byte - (PREV_LINES)] == '\n')
		{
			getstr(strt_byte, cur_byte - (PREV_LINES) - 1, act_buf, &(*line));
			cur_byte++;
			break;
		}
		if (cur_byte - (PREV_LINES) >= BUFF_SIZE - 1)
		{
			*line = ft_strjoin(*line, buf);
			getstr(strt_byte, BUFF_SIZE - 1, act_buf, &(*line));
			line_ct++;
			cur_byte++;
			if (read(fd, &act_buf, BUFF_SIZE) == 0)
				return (0);
		}
		cur_byte++;
	}
	return (0);
}
