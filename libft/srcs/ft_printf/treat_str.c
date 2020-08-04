/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:46:29 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:51:24 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_preci_s(t_format *fmt)
{
	char	*tmp;
	int		len;

	len = (int)ft_strlen(fmt->res);
	if (len > fmt->preci && fmt->preci >= 0)
	{
		if (!(tmp = ft_strnew(fmt->preci)))
			return (0);
		ft_strncpy(tmp, fmt->res, fmt->preci);
		free(fmt->res);
		fmt->res = tmp;
	}
	return (1);
}

int			treat_str(t_format *fmt)
{
	if (!(fmt->res = ft_strdup(va_arg(*(fmt->ap), char*))))
		fmt->res = ft_strdup("(null)");
	if (!(set_preci_s(fmt)))
		return (0);
	if (fmt->width > (int)ft_strlen(fmt->res))
		if (!(set_width(fmt)))
			return (0);
	if (fmt->cap == 1)
		ft_capitalize(fmt->res);
	fmt->ret = ft_strlen(fmt->res);
	return (1);
}
