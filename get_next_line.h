/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:38:01 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/18 00:27:51 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

# define BUFF_SIZE 32

char	*fill_return(int start, int length, char buffer[]);
int		get_length_till_newline(char buf[], int start);
int		get_next_line(const int fd, char **line);

#endif
