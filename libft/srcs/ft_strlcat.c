/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:03:53 by evogel            #+#    #+#             */
/*   Updated: 2018/11/20 15:52:25 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	j = 0;
	while (i < size && dst[i])
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	else
	{
		res = i;
		while (i < size - 1 && src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (res + ft_strlen(src));
}
