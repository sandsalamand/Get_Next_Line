/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:47:04 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/10/06 02:53:10 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	if (argc != 2) {
		ft_putendl("file name needed");
		return (0);
	}
	line = malloc(sizeof(char) * 5);
	line[0] = 'E';
	free(line);
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while (i < 7)
	{
		putnbr_endl(get_next_line(fd, &line));
		//get_next_line(fd, &line);
		ft_putendl(line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

