/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/26 03:23:42 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define PREV_LINES BUFF_SIZE * (*v).line_ct

int		check_buf(t_vars *v, char **buf, int fd, char **line)
{
	(*buf)[(*v).ctr] = (*v).act_buf[(*v).cur_byte - (PREV_LINES)];
	if ((*v).act_buf[(*v).cur_byte - (PREV_LINES)] == '\n')
	{
		(*buf)[(*v).ctr] = '\0';
		*line = ft_strjoin(*line, *buf);
		free(*buf);
		(*v).cur_byte++;
		return (1);
	}
	if ((*v).cur_byte - (PREV_LINES) >= BUFF_SIZE - 1)
	{
		*line = ft_strjoin(*line, *buf);
		ft_strclr(*buf);
		(*v).line_ct++;
		(*v).ctr = 0;
		(*v).cur_byte++;
		if (read(fd, &((*v).act_buf), BUFF_SIZE) == 0)
		{
			free(*buf);
			return (0);
		}
	}
	return (2);
}

int		get_next_line(const int fd, char **line)
{
	static t_vars	vars = {0, 0, {}, 0};
	t_vars			*v;
	char			*buf;
	int				output;	

	v = &vars;
	if ((*v).cur_byte - PREV_LINES == 0)
	{
		if (!(*line))
			*line = ft_strnew(1);
		if (read(fd, &(*v).act_buf, BUFF_SIZE) < 0)
			return (-1);
	}
	buf = ft_strnew((BUFF_SIZE * ((*v).line_ct + 1)) - 1);
	(*v).ctr = 0;
	while ((*v).act_buf[(*v).cur_byte - (PREV_LINES)])
	{
		if ((output = check_buf(v, &buf, fd, line)) == 0)
			return (0);
		else if (output == 1)
			return (1);
		else
		{
			(*v).ctr++;
			(*v).cur_byte++;
		}
	}
	return (0);
}
