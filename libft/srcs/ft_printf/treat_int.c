/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:34:02 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:50:45 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		treat_int(t_format *fmt)
{
	long long d;

	d = get_int(fmt);
	fmt->neg = (d < 0 ? 1 : 0);
	if (!(fmt->res = ft_itoa(d)))
		return (0);
	if (!(set_preci(fmt)))
		return (0);
	if (d >= 0 && (fmt->flag[3] == 1 || fmt->flag[4] == 1))
		if (!(set_prefx(fmt)))
			return (0);
	if (fmt->width > (int)ft_strlen(fmt->res))
		if (!(set_width(fmt)))
			return (0);
	fmt->ret = ft_strlen(fmt->res);
	return (1);
}
