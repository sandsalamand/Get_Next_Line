/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/29 03:30:05 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_buf(t_vars *v, char **buf, int fd, char **line)
{
	(*buf)[(*v).ctr] = (*v).act_buf[(*v).cur_byte];
	if ((*v).act_buf[(*v).cur_byte] == '\n')
	{
		(*buf)[(*v).ctr] = '\0';
		*line = ft_strjoin(*line, *buf);
		free(*buf);
		(*v).cur_byte++;
		return (1);
	}
	if ((*v).cur_byte >= BUFF_SIZE - 1)
	{
		*line = ft_strjoin(*line, *buf);
		ft_strclr(*buf);
		(*v).cur_byte = 0;
		if (((*v).ctr = read(fd, &((*v).act_buf), BUFF_SIZE)) <= 0)
		{
			free(*buf);
			return ((*v).ctr);
		}
		(*v).ctr = 0;
		return (3);
	}
	return (2);
}

int			get_next_line(const int fd, char **line)
{
	static t_vars	vars = {0, {}, 0};
	t_vars			*v;
	char			*buf;
	int				output;	

	v = &vars;
	*line = ft_strnew(1);
	if ((*v).cur_byte == 0)
	{
		if (read(fd, &(*v).act_buf, BUFF_SIZE) < 0)
			return (-1);
	}
	buf = ft_strnew(BUFF_SIZE + 1);
	(*v).ctr = 0;
	while ((*v).act_buf[(*v).cur_byte])
	{
		if ((output = check_buf(v, &buf, fd, line)) != 2 && output != 3)
			return (output);
		else if (output != 3)
		{
			(*v).ctr++;
			(*v).cur_byte++;
		}
	}
	return (0);
}
