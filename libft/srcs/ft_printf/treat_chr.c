/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:54:03 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:50:22 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		treat_chr(t_format *fmt)
{
	char c;

	c = (fmt->conv == '%' ? '%' : (char)va_arg(*(fmt->ap), int));
	if (!(fmt->res = ft_strnew(1)))
		return (0);
	fmt->res[0] = c;
	if (fmt->width > 1)
	{
		if (!(set_width(fmt)))
			return (0);
		fmt->ret = fmt->width;
	}
	else
		fmt->ret = 1;
	if (fmt->cap == 1)
		ft_capitalize(fmt->res);
	return (1);
}
