/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fmt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:21:03 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:47:46 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Tout est set a zero dans memalloc
** preci doit etre -1 parce qu'une precision de 0 existe
** Initialisation des strings des convertisseurs corespondant a un certain type
** Init de tableau de fonctions correspondant aux types
*/

static void		init_format(t_format *fmt)
{
	fmt->res = NULL;
	fmt->preci = -1;
	ft_strcpy(fmt->supp, "%dDioOuUxXcCsSpfFbB");
	ft_strcpy(fmt->type[0], "dDi");
	ft_strcpy(fmt->type[1], "oOuUxXpbB");
	ft_strcpy(fmt->type[2], "sS");
	ft_strcpy(fmt->type[3], "cC%");
	ft_strcpy(fmt->type[4], "fF");
	ft_strcpy(fmt->caps, "XCSB");
	ft_strcpy(fmt->llen, "DOUF");
	fmt->treat_type[0] = &treat_int;
	fmt->treat_type[1] = &treat_uns;
	fmt->treat_type[2] = &treat_str;
	fmt->treat_type[3] = &treat_chr;
	fmt->treat_type[4] = &treat_flt;
}

/*
** get_format initialise la structure
** lis les flags
** puis la width
** puis la precision
** puis la taille de l'argument (l, hh, etc)
** puis le convertisseur
** et choisi une base selon le convertisseur
*/

t_format		*get_format(va_list *ap, const char **format)
{
	t_format	*fmt;

	if (!(fmt = (t_format*)ft_memalloc(sizeof(t_format))))
		return (NULL);
	fmt->ap = ap;
	init_format(fmt);
	while (get_flag(**format, fmt) == 1)
		++(*format);
	get_field(format, fmt);
	get_field(format, fmt);
	get_length(format, fmt);
	if (!get_converter(format, fmt))
	{
		free(fmt);
		return (NULL);
	}
	get_base(fmt);
	return (fmt);
}
