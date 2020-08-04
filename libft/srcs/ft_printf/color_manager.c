/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:38:26 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:44:48 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Initialise colors
** [i][0] being names, and [i][1] being corresponding code
** For  more complex colors:
** for i = 24 & i = 25, color is inputted as arg (0 to 255)
*/

void	init_colors3(t_colors *col)
{
	ft_strcpy(col->colors[24][0], "#");
	ft_strcpy(col->colors[25][0], "##");
	ft_strcpy(col->colors[24][1], "\033[38;5;");
	ft_strcpy(col->colors[25][1], "\033[48;5;");
}

void	init_colors1(t_colors *col)
{
	ft_strcpy(col->colors[0][0], "black");
	ft_strcpy(col->colors[1][0], "b_black");
	ft_strcpy(col->colors[2][0], "bb_black");
	ft_strcpy(col->colors[3][0], "red");
	ft_strcpy(col->colors[4][0], "b_red");
	ft_strcpy(col->colors[5][0], "bb_red");
	ft_strcpy(col->colors[6][0], "green");
	ft_strcpy(col->colors[7][0], "b_green");
	ft_strcpy(col->colors[8][0], "bb_green");
	ft_strcpy(col->colors[9][0], "yellow");
	ft_strcpy(col->colors[10][0], "b_yellow");
	ft_strcpy(col->colors[11][0], "bb_yellow");
	ft_strcpy(col->colors[12][0], "blue");
	ft_strcpy(col->colors[13][0], "b_blue");
	ft_strcpy(col->colors[14][0], "bb_blue");
	ft_strcpy(col->colors[15][0], "magenta");
	ft_strcpy(col->colors[16][0], "b_magenta");
	ft_strcpy(col->colors[17][0], "bb_magenta");
	ft_strcpy(col->colors[18][0], "cyan");
	ft_strcpy(col->colors[19][0], "b_cyan");
	ft_strcpy(col->colors[20][0], "bb_cyan");
	ft_strcpy(col->colors[21][0], "white");
	ft_strcpy(col->colors[22][0], "b_white");
	ft_strcpy(col->colors[23][0], "bb_white");
	ft_strcpy(col->colors[26][0], "eoc");
}

void	init_colors2(t_colors *col)
{
	ft_strcpy(col->colors[0][1], "\033[0;30m");
	ft_strcpy(col->colors[1][1], "\033[1;30m");
	ft_strcpy(col->colors[2][1], "\033[1;40m");
	ft_strcpy(col->colors[3][1], "\033[0;31m");
	ft_strcpy(col->colors[4][1], "\033[1;31m");
	ft_strcpy(col->colors[5][1], "\033[1;41m");
	ft_strcpy(col->colors[6][1], "\033[0;32m");
	ft_strcpy(col->colors[7][1], "\033[1;32m");
	ft_strcpy(col->colors[8][1], "\033[1;42m");
	ft_strcpy(col->colors[9][1], "\033[0;33m");
	ft_strcpy(col->colors[10][1], "\033[1;33m");
	ft_strcpy(col->colors[11][1], "\033[1;43m");
	ft_strcpy(col->colors[12][1], "\033[0;34m");
	ft_strcpy(col->colors[13][1], "\033[1;34m");
	ft_strcpy(col->colors[14][1], "\033[1;44m");
	ft_strcpy(col->colors[15][1], "\033[0;35m");
	ft_strcpy(col->colors[16][1], "\033[1;35m");
	ft_strcpy(col->colors[17][1], "\033[1;45m");
	ft_strcpy(col->colors[18][1], "\033[0;36m");
	ft_strcpy(col->colors[19][1], "\033[1;36m");
	ft_strcpy(col->colors[20][1], "\033[1;46m");
	ft_strcpy(col->colors[21][1], "\033[0;37m");
	ft_strcpy(col->colors[22][1], "\033[1;37m");
	ft_strcpy(col->colors[23][1], "\033[1;47m");
	ft_strcpy(col->colors[26][1], "\033[0m");
}

int		color_manager(va_list *ap, const char **format)
{
	t_colors	*col;
	int			i;

	if (!(col = (t_colors*)ft_memalloc(sizeof(t_colors))))
		return (0);
	init_colors1(col);
	init_colors2(col);
	init_colors3(col);
	i = 0;
	while (ft_strcmp(*format + 1, col->colors[i][0]) != '}' && i < 27)
		++i;
	if (i != 27)
	{
		ft_putstr(col->colors[i][1]);
		if (i == 24 || i == 25)
		{
			ft_putnbr((unsigned char)va_arg(*ap, int));
			ft_putchar('m');
		}
		while (**format != '}')
			++(*format);
		++(*format);
	}
	free(col);
	return (i == 27 ? 0 : 1);
}
