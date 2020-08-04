/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:57:17 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:21:52 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# include <strings.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct		s_format
{
	va_list *ap;
	char	*res;
	int		ret;

	char	conv;
	char	supp[20];
	char	type[5][10];
	int		(*treat_type[5])(struct s_format*);
	char	caps[5];
	char	llen[5];

	int		width;
	int		preci;

	int		flag[7];
	int		length[5];

	int		neg;
	int		cap;
	char	base[26];
}					t_format;

/*
** Note structure array value represetations:
**
** HASH : fmt->flag[0]
** ZERO : fmt->flag[1]
** MINUS: fmt->flag[2]
** PLUS : fmt->flag[3]
** SPACE: fmt->flag[4]
** FILL : fmt->flag[5]
** MID  : fmt->flag[6]
**
** H : fmt->length[0]
** HH: fmt->length[1]
** L : fmt->length[2]
** LL: fmt->length[3]
** FL: fmt->length[4]
**
** INTS: fmt->type[0]
** UNSI: fmt->type[1]
** STRI: fmt->type[2]
** CHAR: fmt->type[3]
** FLOT: fmt->type[4]
*/

int					ft_printf(const char *fmt, ...);
int					converter(va_list *ap, const char **format);
int					treatment(t_format *fmt);

t_format			*get_format(va_list *ap, const char **format);
int					get_flag(char c, t_format *fmt);
void				get_field(const char **format, t_format *fmt);
void				get_length(const char **format, t_format *fmt);
int					get_converter(const char **format, t_format *fmt);
void				get_base(t_format *fmt);

int					treat_int(t_format *fmt);
int					treat_uns(t_format *fmt);
int					treat_chr(t_format *fmt);
int					treat_str(t_format *fmt);
int					treat_flt(t_format *fmt);

long long			get_int(t_format *fmt);
unsigned long long	get_uns(t_format *fmt);
long double			get_flt(t_format *fmt);

int					set_preci(t_format *fmt);
int					set_prefx(t_format *fmt);
int					set_width(t_format *fmt);

/*
** Struct and function for color options
*/

typedef struct		s_colors
{
	char	colors[27][2][20];
}					t_colors;

int					color_manager(va_list *ap, const char **format);

#endif
