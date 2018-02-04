/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 16:04:29 by pribault          #+#    #+#             */
/*   Updated: 2017/10/23 20:22:18 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdump(void *ptr, size_t size)
{
	size_t	i;

	if (!ptr)
		return ;
	i = 0;
	while (i < size)
	{
		ft_printf((i) ? " %.2hhx" : "%.2hhx", ((char*)ptr)[i]);
		i++;
	}
	ft_putchar('\n');
}
