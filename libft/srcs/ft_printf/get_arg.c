/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:02:30 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:47:33 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long			get_int(t_format *fmt)
{
	long long d;

	if (fmt->length[2])
		d = (long long)va_arg(*(fmt->ap), long);
	else if (fmt->length[3])
		d = va_arg(*(fmt->ap), long long);
	else if (fmt->length[0])
		d = (short)va_arg(*(fmt->ap), int);
	else if (fmt->length[1])
		d = (char)va_arg(*(fmt->ap), int);
	else
		d = (long long)va_arg(*(fmt->ap), int);
	return (d);
}

unsigned long long	get_uns(t_format *fmt)
{
	unsigned long long u;

	if (fmt->length[2])
		u = (unsigned long long)va_arg(*(fmt->ap), unsigned long);
	else if (fmt->length[3] || fmt->conv == 'p')
		u = va_arg(*(fmt->ap), unsigned long long);
	else if (fmt->length[0])
		u = (unsigned short)va_arg(*(fmt->ap), unsigned int);
	else if (fmt->length[1])
		u = (unsigned char)va_arg(*(fmt->ap), unsigned int);
	else
		u = (unsigned long long)va_arg(*(fmt->ap), unsigned int);
	return (u);
}

long double			get_flt(t_format *fmt)
{
	long double f;

	if (fmt->length[4])
		f = va_arg(*(fmt->ap), long double);
	else
		f = (long double)va_arg(*(fmt->ap), double);
	return (f);
}
