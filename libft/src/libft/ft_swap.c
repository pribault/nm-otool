/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:03:37 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 17:14:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap_2(void *a, void *b, size_t size, size_t i)
{
	while (i + 1 < size)
	{
		*(uint16_t*)(a + i) ^= *(uint16_t*)(b + i);
		*(uint16_t*)(b + i) ^= *(uint16_t*)(a + i);
		*(uint16_t*)(a + i) ^= *(uint16_t*)(b + i);
		i += 2;
	}
	while (i < size)
	{
		*(uint8_t*)(a + i) ^= *(uint8_t*)(b + i);
		*(uint8_t*)(b + i) ^= *(uint8_t*)(a + i);
		*(uint8_t*)(a + i) ^= *(uint8_t*)(b + i);
		i++;
	}
}

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
	while (i + 3 < size)
	{
		*(uint32_t*)(a + i) ^= *(uint32_t*)(b + i);
		*(uint32_t*)(b + i) ^= *(uint32_t*)(a + i);
		*(uint32_t*)(a + i) ^= *(uint32_t*)(b + i);
		i += 4;
	}
	ft_swap_2(a, b, size, i);
}
