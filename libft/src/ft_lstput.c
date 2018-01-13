/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:10:14 by pribault          #+#    #+#             */
/*   Updated: 2017/10/25 16:56:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstput(t_list **head, t_list *new, size_t n)
{
	t_list	*list;
	size_t	i;

	if (!head)
		return ;
	if (!n)
	{
		new->next = *head;
		return ((void)(*head = new));
	}
	n--;
	list = *head;
	i = 0;
	while (i < n && list->next)
	{
		list = list->next;
		i++;
	}
	new->next = list->next;
	list->next = new;
}
