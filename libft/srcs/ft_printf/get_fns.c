/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 11:32:05 by evogel            #+#    #+#             */
/*   Updated: 2019/05/17 14:48:56 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_flag(char c, t_format *fmt)
{
	if (c == '#' && (fmt->flag[0] = 1))
		return (1);
	else if (c == '0' && (fmt->flag[1] = 1))
		return (1);
	else if (c == '-' && (fmt->flag[2] = 1))
		return (1);
	else if (c == '+' && (fmt->flag[3] = 1))
		return (1);
	else if (c == ' ' && (fmt->flag[4] = 1))
		return (1);
	else if (c == '_' && (fmt->flag[5] = (char)va_arg(*(fmt->ap), int)))
		return (1);
	else if (c == '|' && (fmt->flag[6] = 1))
		return (1);
	return (0);
}

void	get_field(const char **format, t_format *fmt)
{
	int	*n;
	int	tmp;

	if ((**format == '.' && ++(*format)) || (fmt->width && **format == '*'))
	{
		n = &fmt->preci;
		*n = 0;
	}
	else
		n = &fmt->width;
	tmp = 0;
	while (ft_isdigit(**format) == 1)
	{
		tmp = tmp * 10 + (**format - '0');
		*n = tmp;
		++(*format);
	}
	if (**format == '*' && ++(*format))
	{
		*n = va_arg(*(fmt->ap), int);
		if (n == &fmt->width && *n < 0 && (fmt->flag[2] = 1))
			*n = *n * -1;
	}
}

void	get_length(const char **format, t_format *fmt)
{
	if (**format == 'l')
	{
		++(*format);
		if (**format == 'l' && ++(*format))
			fmt->length[3] = 1;
		else
			fmt->length[2] = 1;
	}
	else if (**format == 'h')
	{
		++(*format);
		if (**format == 'h' && ++(*format))
			fmt->length[1] = 1;
		else
			fmt->length[0] = 1;
	}
	else if (**format == 'L' && ++(*format))
		fmt->length[4] = 1;
}

int		get_converter(const char **format, t_format *fmt)
{
	if (**format == '\0' || !ft_strchr(fmt->supp, **format))
		return (0);
	fmt->conv = **format;
	++(*format);
	if (ft_strchr(fmt->caps, fmt->conv))
	{
		fmt->cap = 1;
		fmt->conv = fmt->conv + 32;
	}
	if (ft_strchr(fmt->llen, fmt->conv))
	{
		if (fmt->length[2] == 1 && (fmt->length[3] = 1))
			fmt->length[2] = 0;
		else
			fmt->length[2] = 1;
		fmt->conv = fmt->conv + 32;
	}
	return (1);
}

void	get_base(t_format *fmt)
{
	if (fmt->conv == 'o')
		ft_strcpy(fmt->base, "01234567");
	else if (fmt->conv == 'x' || fmt->conv == 'p')
		ft_strcpy(fmt->base, "0123456789abcdef");
	else if (fmt->conv == 'b')
		ft_strcpy(fmt->base, va_arg(*(fmt->ap), char*));
	else
		ft_strcpy(fmt->base, "0123456789");
}
