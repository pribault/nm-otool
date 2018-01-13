/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:53:21 by pribault          #+#    #+#             */
/*   Updated: 2017/10/25 15:57:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(t_list *head, size_t n)
{
	t_list	*list;
	size_t	i;

	list = head;
	i = 0;
	while (i < n && list)
	{
		list = list->next;
		i++;
	}
	return (list);
}
