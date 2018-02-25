/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:03:37 by pribault          #+#    #+#             */
/*   Updated: 2018/02/25 11:46:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_swap(void *a, void *b, size_t size)
{
	size_t	i;

	if (!a || !b)
		return ;
	i = 0;
	while (i + 7 < size)
	{
		*(uint64_t*)(a + i) ^= *(uint64_t*)(b + i);
		*(uint64_t*)(b + i) ^= *(uint64_t*)(a + i);
		*(uint64_t*)(a + i) ^= *(uint64_t*)(b + i);
		i += 8;
	}
	while (i < size)
	{
		*(uint8_t*)(a + i) ^= *(uint8_t*)(b + i);
		*(uint8_t*)(b + i) ^= *(uint8_t*)(a + i);
		*(uint8_t*)(a + i) ^= *(uint8_t*)(b + i);
		i++;
	}
}
