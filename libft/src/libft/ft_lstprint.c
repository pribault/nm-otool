/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:29:31 by pribault          #+#    #+#             */
/*   Updated: 2017/10/25 16:54:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *head, void (*print)(void*))
{
	ft_putchar('[');
	while (head)
	{
		print(head->content);
		head = head->next;
		ft_putstr("] -> [");
	}
	ft_putendl("\033[0m\033[38;5;124mnull\033[0m]");
}
