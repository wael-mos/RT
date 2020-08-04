/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ppw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:25:52 by evogel            #+#    #+#             */
/*   Updated: 2019/05/17 14:49:14 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Preci mallocs at new size filled with zeros
** copies res into new string at correct position, leving zeros in front
** puts back minus in front of all zeros if necessary
** When the number and precision both 0, res is empty
*/

int			set_preci(t_format *fmt)
{
	int		len;
	char	*tmp;

	len = ft_strlen(fmt->res) - fmt->neg;
	if (fmt->preci > len)
	{
		if (!(tmp = ft_setmalloc(fmt->preci + fmt->neg, '0')))
			return (0);
		ft_strcpy(tmp + (fmt->preci - len) + fmt->neg, fmt->res + fmt->neg);
		if (fmt->neg)
			tmp[0] = '-';
		free(fmt->res);
		fmt->res = tmp;
	}
	else if (fmt->preci == 0 && fmt->res[0] == '0')
	{
		if (!(tmp = ft_strnew(0)))
			return (0);
		free(fmt->res);
		fmt->res = tmp;
	}
	return (1);
}

/*
** Mallocs +1 or +2 depending on type of prefix needed
** copies back res with proper increment (1 or 2)
** then copies prefix:
** prefix of '+' or ' ' for non base numbers
** prefix of 0x for hex
*/

int			set_prefx(t_format *fmt)
{
	char	*tmp;
	int		add;

	add = (fmt->conv == 'x' || fmt->conv == 'p' ? 2 : 1);
	if (!(tmp = ft_setmalloc(ft_strlen(fmt->res) + add, '0')))
		return (0);
	ft_strcpy(tmp + add, fmt->res);
	if (fmt->conv != 'x' && fmt->conv != 'o' && fmt->conv != 'p')
		tmp[0] = (fmt->flag[3] ? '+' : ' ');
	else if (fmt->conv == 'x' || fmt->conv == 'p')
		tmp[1] = 'x';
	free(fmt->res);
	fmt->res = tmp;
	return (1);
}

/*
** When getting len, len is 1 for char conv
** Get correct char to fill spaces with: '0' or ' ' or arg depending
** Create new string with filler char
** copy back original string following certain conditions:
** when copying in front, make sure str doesn't end early because of copied '\0'
** when '0' fill && prefix, copy at end without prefix then add prefix in front
** in all other cases, copy at end normally
*/

static int	zero_fill(t_format *fmt)
{
	if (fmt->conv == 's' || fmt->conv == 'c')
		return (0);
	else if (fmt->flag[0] && fmt->conv == 'x' && fmt->res[1])
		return (2);
	else if (fmt->conv != 'x' && (fmt->flag[3] || fmt->flag[4] || fmt->neg))
		return (1);
	return (0);
}

static char	get_char(t_format *fmt)
{
	if (fmt->flag[5])
		return (fmt->flag[5]);
	else if (fmt->flag[1] && !fmt->flag[2] && !fmt->flag[6]
			&& (fmt->preci < 0 || ft_strchr("fsc%", fmt->conv)))
		return ('0');
	else
		return (' ');
}

int			set_width(t_format *fmt)
{
	char	c;
	char	*tmp;
	int		len;
	int		add;

	len = (fmt->conv == 'c' ? 1 : (int)ft_strlen(fmt->res));
	c = get_char(fmt);
	if (!(tmp = ft_setmalloc(fmt->width, c)))
		return (0);
	if (fmt->flag[6] == 1)
		ft_memcpy(tmp + (fmt->width / 2) - (len / 2), fmt->res, len);
	else if (fmt->flag[2] && ft_memcpy(tmp, fmt->res, len))
		tmp[len] = c;
	else if (c == '0' && (add = zero_fill(fmt)))
	{
		ft_memcpy(tmp + (fmt->width - len) + add, fmt->res + add, len - add);
		tmp[add - 1] = fmt->res[add - 1];
	}
	else
		ft_memcpy(tmp + (fmt->width - len), fmt->res, len);
	free(fmt->res);
	fmt->res = tmp;
	return (1);
}
