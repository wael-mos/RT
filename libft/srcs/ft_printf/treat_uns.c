/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_uns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 11:33:39 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:51:53 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Prefix condition:
** when preci already put 0 in front of octal, no need to add prefix
** hexa no prefix when 0
*/

int			treat_uns(t_format *fmt)
{
	unsigned long long u;

	u = get_uns(fmt);
	if (!(fmt->res = ft_itoabase(u, fmt->base)))
		return (0);
	if (!(set_preci(fmt)))
		return (0);
	if ((fmt->flag[0] && ((fmt->conv == 'o' && fmt->res[0] != '0')
					|| (fmt->conv == 'x' && u != 0))) || fmt->conv == 'p')
		if (!(set_prefx(fmt)))
			return (0);
	if (fmt->width > (int)ft_strlen(fmt->res))
		if (!(set_width(fmt)))
			return (0);
	if (fmt->cap == 1)
		ft_capitalize(fmt->res);
	fmt->ret = ft_strlen(fmt->res);
	return (1);
}
