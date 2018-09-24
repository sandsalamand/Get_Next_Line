/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:38:01 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/23 00:39:33 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
#include <stdio.h>

# define BUFF_SIZE 32

typedef struct		s_vars
{		
	int				cur_byte;
	int				line_ct;
	char			act_buf[BUFF_SIZE];
//	int				ctr;
}					t_vars;

int		get_next_line(const int fd, char **line);

#endif
