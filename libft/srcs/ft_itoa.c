/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:22:11 by evogel            #+#    #+#             */
/*   Updated: 2020/07/15 13:34:44 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(unsigned long long n)
{
	int		len;

	len = 1;
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(long long n)
{
	int					len;
	unsigned long long	nb;
	char				*num;
	int					neg;

	neg = (n < 0 ? 1 : 0);
	nb = (neg == 1 ? -n : n);
	len = get_len(nb) + neg;
	if (!(num = ft_strnew(len + neg)))
		return (NULL);
	if (neg == 1)
		num[0] = '-';
	while (--len >= neg)
	{
		num[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (num);
}
