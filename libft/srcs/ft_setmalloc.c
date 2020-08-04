/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:31:42 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 15:07:48 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_setmalloc(size_t size, int c)
{
	char	*res;

	if (!(res = ft_strnew(size)))
		return (NULL);
	ft_memset(res, c, size);
	return (res);
}
