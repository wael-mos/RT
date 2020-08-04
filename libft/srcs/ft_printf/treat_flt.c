/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_flt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:32:17 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:50:38 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		treat_flt(t_format *fmt)
{
	long double f;

	f = get_flt(fmt);
	fmt->res = ft_flotoa(f, (fmt->preci == -1 ? 6 : fmt->preci));
	if (f >= 0 && (fmt->flag[3] == 1 || fmt->flag[4] == 1))
		if (!(set_prefx(fmt)))
			return (0);
	if (fmt->width > (int)ft_strlen(fmt->res))
		if (!(set_width(fmt)))
			return (0);
	fmt->ret = ft_strlen(fmt->res);
	return (1);
}
