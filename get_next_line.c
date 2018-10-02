/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:48:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/10/01 21:57:17 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	e_read(t_vars *v, char **line, char **buf, int fd)
{
	int output;
	int	i;

	output = read(fd, &((*v).act_buf), BUFF_SIZE);
	if (output < 0 || fd < 0 || *line == NULL)
	{
		ft_strdel(buf);
		return (-1);
	}
	if (output < BUFF_SIZE && output > 0)
	{
		strnclr(*buf, BUFF_SIZE);
		i = 0;
		while ((*v).act_buf[i + 1])
		{
			(*buf)[i] = (*v).act_buf[i];
			i++;
		}
		ft_strjoin(*line, *buf);
		ft_strdel(buf);
		return (0);
	}
	return(1);
}

static int	check_buf(t_vars *v, char **buf, int fd, char **line)
{
	(*buf)[(*v).ctr] = (*v).act_buf[(*v).cur_byte];
	if ((*v).act_buf[(*v).cur_byte] == '\n')
	{
		(*buf)[(*v).ctr] = '\0';
		*line = ft_strjoin(*line, *buf);
		ft_strdel(buf);
		(*v).cur_byte++;
		return (1);
	}
	if ((*v).cur_byte >= BUFF_SIZE - 1)
	{
		*line = ft_strjoin(*line, *buf);
		strnclr(*buf, BUFF_SIZE);
		(*v).cur_byte = 0;
		if (((*v).ctr = e_read(v, line, buf, fd)) <= 0)
			return ((*v).ctr);
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
		if ((output = e_read(v, line, &buf, fd)) <= 0)
			return (output);
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
