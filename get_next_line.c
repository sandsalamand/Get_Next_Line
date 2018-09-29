#include "get_next_line.h"
#define PREV_LINES BUFF_SIZE * v.line_ct

int		get_next_line(const int fd, char **line)
{
	static t_vars	v = {0, 0, {}};
	char			*buf;
	int				cntr;

	*line = ft_strnew(1);
	if (v.cur_byte == 0)
	{
		if (read(fd, &v.act_buf, BUFF_SIZE) < 0)
			return (-1);
	}
	buf = ft_strnew((BUFF_SIZE * (v.line_ct + 1)) - 1);
	cntr = 0;
	while (v.act_buf[v.cur_byte - (PREV_LINES)])
	{
		buf[cntr] = v.act_buf[v.cur_byte - (PREV_LINES)];
		if (v.act_buf[v.cur_byte - (PREV_LINES)] == '\n')
		{
			buf[cntr] = '\0';
			*line = ft_strjoin(*line, buf);
			free(buf);
			v.cur_byte++;
			return(1);
		}
		if (v.cur_byte - (PREV_LINES) >= BUFF_SIZE - 1)
		{
			*line = ft_strjoin(*line, buf);
			ft_strclr(buf);
			v.line_ct++;
			cntr = 0;
			v.cur_byte++;
			if (read(fd, &(v.act_buf), BUFF_SIZE) == 0)
			{
				free(buf);
				return (0);
			}
		}
		else
		{
			cntr++;
			v.cur_byte++;
		}
	}
	return (0);
}
