/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 20:24:06 by pribault          #+#    #+#             */
/*   Updated: 2017/10/29 12:47:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstsort(t_list *head, int (*sort)(void*, void*))
{
	t_list	*list;
	int		stop;

	if (!head || !sort)
		return ;
	stop = 1;
	while (stop)
	{
		list = head;
		stop = 0;
		while (list->next)
		{
			if (sort(list->content, list->next->content) > 0)
			{
				ft_swap(&list->content, &list->next->content);
				stop = 1;
			}
			list = list->next;
		}
	}
}
