/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 11:27:52 by evogel            #+#    #+#             */
/*   Updated: 2019/03/20 14:44:12 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*new_fd(size_t fd)
{
	t_list	*new;

	if (!(new = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!(new->content = ft_memalloc(sizeof(char))))
	{
		free(new);
		return (NULL);
	}
	new->content_size = fd;
	new->next = NULL;
	return (new);
}

static t_list	*get_fd(size_t fd, t_list **begin)
{
	t_list	*lst;
	t_list	*new;

	lst = *begin;
	while (lst)
	{
		if (lst->content_size == fd)
			return (lst);
		lst = lst->next;
	}
	if (!(new = new_fd(fd)))
		return (NULL);
	ft_lstadd(begin, new);
	return (new);
}

static int		read_fd(t_list *current)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;

	while ((ret = read((int)current->content_size, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = (char*)current->content;
		if (!(current->content = (void*)ft_strjoin(current->content, buff)))
			return (-1);
		free(tmp);
		if (ft_strchr((char*)current->content, '\n'))
			break ;
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*begin = NULL;
	t_list			*current;
	int				ret;
	char			*eol;
	char			*tmp;

	if (fd < 0 || line == NULL || !(current = get_fd(fd, &begin)))
		return (-1);
	if ((ret = read_fd(current)) == -1)
		return (-1);
	if (ret == 0 && *(char*)current->content == '\0')
		return (0);
	if (!(eol = ft_strchr((char*)current->content, '\n')) && ret == 0)
		eol = ft_strchr((char*)current->content, '\0');
	*line = ft_strsub(current->content, 0, eol - (char*)current->content);
	if (*line == NULL)
		return (-1);
	tmp = (char*)current->content;
	current->content = (void*)(*eol == 0 ? ft_strdup(eol) : ft_strdup(eol + 1));
	free(tmp);
	if (*line == NULL || current->content == NULL)
		return (-1);
	return (1);
}
