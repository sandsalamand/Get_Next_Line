#include "get_next_line.h"

static char	*strnjoin_arg2(char *s1, char s2[BUFF_SIZE], int start, int end)
{
	char		*result;
	size_t		str1len;
	size_t		i;

	str1len = ft_strlen(s1);
	result = (char*)malloc(sizeof(char) * (str1len + end - start + 2));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < str1len)
	{
		result[i] = s1[i];
		i++;
	}
	while (start <= end)
	{
		result[i] = s2[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

int			get_next_line(int fd, char **line)
{
	static int	cur_byte = 0;
	static char	buffer[BUFF_SIZE];
	int			res;

	if (cur_byte == 0 || cur_byte >= BUFF_SIZE)
	{
		res = read(fd, buffer, BUFF_SIZE);
		cur_byte = 0;
	}
	buffer[BUFF_SIZE] = '\0';
	if (res == -1)
		return (-1);
	if (res == 0)
		return (0);
	res = 0;
	while (res < BUFF_SIZE)
	{
		if (buffer[res] == '\n')
			break;
		res++;
	}
	*line = strnjoin_arg2(*line, buffer, cur_byte, cur_byte + res);
	cur_byte += res;
	if (res == BUFF_SIZE)
		return (get_next_line(fd, line));
	return (-1);
}
