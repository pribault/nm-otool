/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:04:26 by pribault          #+#    #+#             */
/*   Updated: 2018/02/17 14:01:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i + 7 < n)
	{
		*(uint64_t*)(s + i) = (uint64_t)0;
		i += (8);
	}
	while (i + 3 < n)
	{
		*(uint32_t*)(s + i) = (uint32_t)0;
		i += (4);
	}
	while (i + 1 < n)
	{
		*(uint16_t*)(s + i) = (uint16_t)0;
		i += (2);
	}
	while (i < n)
	{
		*(uint8_t*)(s + i) = (uint8_t)0;
		i++;
	}
}
