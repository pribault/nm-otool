/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:59:35 by pribault          #+#    #+#             */
/*   Updated: 2016/11/09 18:09:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*head;
	t_list		*result;

	if (lst == NULL)
		return (NULL);
	head = f(ft_lstnew(lst->content, lst->content_size));
	result = head;
	while (lst->next != NULL)
	{
		lst = lst->next;
		result->next = f(ft_lstnew(lst->content, lst->content_size));
		result = result->next;
	}
	return (head);
}
