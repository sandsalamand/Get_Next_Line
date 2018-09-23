/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/23 00:41:45 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define PREV_LINES BUFF_SIZE * line_ct

int		get_next_line(const int fd, char **line)
{
	static char		act_buf[BUFF_SIZE];
	static int		cur_byte = 0;
	static int		line_ct = 0;
	char			*buf;
	int				cntr;

	free(*line);
	*line = ft_strnew(1);
	if (cur_byte == 0)
	{
		if (read(fd, &act_buf, BUFF_SIZE) == 0)
			return (0);
	}
	buf = ft_strnew((BUFF_SIZE * (line_ct + 1)) - 1);
	cntr = 0;
	while (act_buf[cur_byte - (PREV_LINES)])
	{
		buf[cntr] = act_buf[cur_byte - (PREV_LINES)];
		if (act_buf[cur_byte - (PREV_LINES)] == '\n')
		{
			buf[cntr] = '\0';
			*line = ft_strjoin(*line, buf);
			free(buf);
			cur_byte++;
			return(0);
		}
		if (cur_byte - (PREV_LINES) >= BUFF_SIZE - 1)
		{
			*line = ft_strjoin(*line, buf);
			ft_strclr(buf);
			line_ct++;
			cntr = 0;
			cur_byte++;
			if (read(fd, &act_buf, BUFF_SIZE) == 0)
			{
				free(buf);
				return (0);
			}
		}
		else
		{
			cntr++;
			cur_byte++;
		}
	}
	return (0);
}
