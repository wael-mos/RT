/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:22:11 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 15:07:17 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(unsigned long long n, size_t base)
{
	int		len;

	len = 1;
	while (n >= (unsigned long long)base)
	{
		len++;
		n /= base;
	}
	return (len);
}

char		*ft_itoabase(unsigned long long n, char *base)
{
	int					len;
	int					n_base;
	char				*num;

	n_base = ft_strlen(base);
	len = get_len(n, n_base);
	if (!(num = ft_strnew(len)))
		return (NULL);
	while (--len >= 0)
	{
		num[len] = base[n % n_base];
		n /= n_base;
	}
	return (num);
}
