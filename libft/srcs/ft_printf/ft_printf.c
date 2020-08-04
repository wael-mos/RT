/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:22:05 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:45:02 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
** treatment cherche quel type d'argument on recupere
** puis appel la fonction traitement correspondant
** int || unsigned || char || string || float
*/

int		treatment(t_format *fmt)
{
	int i;

	i = 0;
	while (!ft_strchr(fmt->type[i], fmt->conv) && i < 5)
		++i;
	if (!fmt->treat_type[i](fmt))
		return (0);
	return (1);
}

/*
** converteur initialise et recupere info du format dans le struct fmt
** puis envoie cette struct au traitement qui interprete et cree le string final
** imprime le string, et free tout avant de quitter
*/

int		converter(va_list *ap, const char **format)
{
	t_format	*fmt;
	int			ret;

	if (!(fmt = get_format(ap, format)))
		return (0);
	if (!treatment(fmt))
	{
		if (fmt->res)
			free(fmt->res);
		free(fmt);
		return (0);
	}
	write(1, fmt->res, fmt->ret);
	ret = fmt->ret;
	free(fmt->res);
	free(fmt);
	return (ret);
}

/*
** Parcours string format
** Quand il trouve un '%' -> envoie au converter qui va interpreter le format,
** imprimer le resultat, renvoyer le nombre de chars imprimes
** Si '{' -> color_manager set le shell a la couleur demande
** Sinon il imprime le char lu
*/

int		ft_printf(const char *format, ...)
{
	va_list ap;
	int		ret;

	ret = 0;
	va_start(ap, format);
	while (format && *format)
	{
		if (*format == '%')
		{
			++format;
			ret += converter(&ap, &format);
		}
		else if (*format == '{')
		{
			if (color_manager(&ap, &format) == 0 && (++ret))
				ft_putchar(*format++);
		}
		else
		{
			ft_putchar(*format++);
			++ret;
		}
	}
	va_end(ap);
	return (ret);
}

/*
** BONUSES :
** -----------------------------------------------------------------------------
** 255 colors!
** 	- 8 standard colors {black,red,green,yellow,blue,magenta,cyan,white}
** 	- 8 bright colors {b_black,b_red,b_green,b_yellow,b_blue,b_magenta,b_cyan,
**		b_white}
** 	- 8 highlight colors {bb_black,bb_red,bb_green,bb_yellow,bb_blue,bb_magenta,
**		bb_cyan,bb_white}
** 	- 255 text colors given as arg with {#}
** 	- 255 highlight colors given as arg with {##}
** -----------------------------------------------------------------------------
** Converters:
**  - b : converts number to any base given as arg (ie. "01", "0abcdefghi")
**	- CSB : any chars in res are capitalised
**	- DOUF : ld, lo, lu, lf, respectively
** -----------------------------------------------------------------------------
** Flags:
**  - '*' : for width or precision given as arg
**	- '_' : for filling extra space with char given as arg
**	- '|' : for adjusting text in center
*/
