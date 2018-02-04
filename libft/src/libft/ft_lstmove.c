/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:26:32 by pribault          #+#    #+#             */
/*   Updated: 2017/10/29 12:03:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmove(t_list **head, size_t from, size_t to)
{
	t_list	*list;
	t_list	*ptr;

	if (!head)
		return ;
	if (from)
	{
		if (!(list = ft_lstget(*head, from - 1)) ||
			!(ptr = list->next))
			return ;
		list->next = ptr->next;
	}
	else
	{
		ptr = *head;
		*head = ptr->next;
	}
	ft_lstput(head, ptr, to);
}
