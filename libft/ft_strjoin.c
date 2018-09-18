/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:00:33 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/09/17 23:05:21 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*result;
	size_t		str1len;
	size_t		str2len;
	size_t		i;

	if (!s1 || !s2)
		return (NULL);
	str1len = ft_strlen(s1);
	str2len = ft_strlen(s2);
	result = (char*)malloc(sizeof(char) * (str1len + str2len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < str1len)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < str1len + str2len)
	{
		result[i] = s2[i - str1len];
		i++;
	}
	result[i] = '\0';
	return (result);
}
