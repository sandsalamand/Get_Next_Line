/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:47:04 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/10/09 22:58:40 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;

	i = 1;
	if (argc != 2) {
		ft_putendl("file name needed");
		return (0);
	}
	line = malloc(sizeof(char) * 5);
	line[0] = 'E';
	free(line);
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while (i != 0 && i != -1)
	{
		i = get_next_line(fd, &line);
		putnbr_endl(i);
		ft_putendl(line);
		free(line);
	}
	close(fd);
	//ft_strdel(&line);
	return (0);
}

