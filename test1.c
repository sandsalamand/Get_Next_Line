/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:47:04 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/17 21:03:44 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main()
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * 5);
	line[0] = 'E';
	fd = open("testfile.txt", O_RDONLY);
	while (i < 5)
	{
		get_next_line(fd, &line);
		ft_putendl(line);
		i++;
	}
	return (0);
}

