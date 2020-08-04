/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 12:10:35 by evogel            #+#    #+#             */
/*   Updated: 2020/07/13 13:56:09 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*make_filename(int n)
{
	char		*filename;

	if (!(filename = ft_strnew(17)))
		return (NULL);
	ft_strcat(filename, "./screenshot");
	filename[12] = n / 10 + '0';
	filename[13] = n % 10 + '0';
	ft_strcat(filename, ".ppm");
	return (filename);
}

static void	convert_agbr_to_argb(unsigned int *idata, unsigned int *data)
{
	int				x;
	int				y;
	unsigned int	tmp;
	unsigned int	bgr[3];

	y = 0;
	while (y < 1008)
	{
		x = 0;
		while (x < 1445)
		{
			tmp = idata[x + y * 1445];
			bgr[0] = ((tmp >> 16) & 0xFF);
			bgr[1] = ((tmp >> 8) & 0xFF);
			bgr[2] = ((tmp) & 0xFF);
			tmp = (255 << 24) | ((uint8_t)bgr[2] << 16) | \
			((uint8_t)bgr[1] << 8) | ((uint8_t)bgr[0]);
			data[x + y * 1445] = tmp;
			++x;
		}
		++y;
	}
}

static void	data_fill_ppm(int fd, t_env *env)
{
	int				i;
	unsigned int	*data;

	data = malloc(sizeof(unsigned int) * 1445 * 1008);
	convert_agbr_to_argb(env->gtk.data, data);
	ft_putendl_fd("P3", fd);
	ft_putnbr_fd(env->scene.win_x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(env->scene.win_y, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(255, fd);
	ft_putchar_fd('\n', fd);
	i = 2;
	while (i < (int)(1445 * 1008 * sizeof(unsigned int)))
	{
		while (i % 4 != 3 && i >= 0)
		{
			ft_putnbr_fd(((unsigned char*)data)[i--], fd);
			ft_putchar_fd(' ', fd);
		}
		i += 7;
	}
	ft_putchar_fd('\n', fd);
	free(data);
}

void		write_ppm(int key, t_env *env)
{
	int		n;
	char	*filename;

	n = 1;
	while (n < 100)
	{
		if (!(filename = make_filename(n)))
			return (ft_putendl("Error creating file"));
		if ((key = open(filename, O_CREAT | O_WRONLY | O_EXCL, 0666)) != -1)
			break ;
		free(filename);
		++n;
	}
	if (n == 100)
		return (ft_putendl("Screenshot limit reached"));
	data_fill_ppm(key, env);
	ft_printf("%s was successfully created\n", filename);
	free(filename);
	close(key);
}

gboolean	screenshot(GtkButton *btn, gpointer data)
{
	t_env *env;

	env = data;
	(void)btn;
	write_ppm(0, env);
	return (TRUE);
}
