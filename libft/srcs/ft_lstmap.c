/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <evogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:15:52 by evogel            #+#    #+#             */
/*   Updated: 2018/11/19 15:47:01 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin;
	t_list	*new;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	new = f(lst);
	begin = new;
	lst = lst->next;
	while (lst && new)
	{
		tmp = f(lst);
		new->next = tmp;
		new = tmp;
		lst = lst->next;
	}
	if (new == NULL)
		ft_lstdel(&begin, ft_bzero);
	return (begin);
}
