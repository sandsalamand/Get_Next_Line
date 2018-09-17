/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:47:04 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/16 21:57:24 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open("testfile.txt", O_RDONLY);
	while (i < 5)
	{
		get_next_line(fd, &line);
		printf("%s\n", line);
		i++;
	}
	return (0);
}

