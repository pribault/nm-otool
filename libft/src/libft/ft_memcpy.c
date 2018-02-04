/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:20:24 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 13:35:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i + 7 < n)
	{
		*(uint64_t*)(dst + i) = *(uint64_t*)(src + i);
		i += (8);
	}
	while (i + 3 < n)
	{
		*(uint32_t*)(dst + i) = *(uint32_t*)(src + i);
		i += (4);
	}
	while (i + 1 < n)
	{
		*(uint16_t*)(dst + i) = *(uint16_t*)(src + i);
		i += (2);
	}
	while (i < n)
	{
		*(uint8_t*)(dst + i) = *(uint8_t*)(src + i);
		i++;
	}
	return (dst);
}
