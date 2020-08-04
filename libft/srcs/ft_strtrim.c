/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:24:44 by evogel            #+#    #+#             */
/*   Updated: 2018/11/16 15:40:01 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static size_t	find_len(char const *s)
{
	int		len;
	int		i;

	len = (int)ft_strlen(s);
	i = len - 1;
	while (check_blank(s[i--]) == 1 && i > -1)
		len--;
	i = 0;
	while (check_blank(s[i++]) == 1)
		len--;
	if (len < 0)
		return (0);
	return (len);
}

char			*ft_strtrim(char const *s)
{
	char	*trim;
	size_t	i;
	size_t	j;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = find_len(s);
	if (!(trim = ft_strnew(len)))
		return (NULL);
	i = 0;
	j = 0;
	while (check_blank(s[i]) == 1)
		i++;
	while (j < len)
		trim[j++] = s[i++];
	return (trim);
}
