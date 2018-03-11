/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:49:57 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 16:51:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	endian(void *ptr, size_t size)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		((uint8_t*)ptr)[i] ^= ((uint8_t*)ptr)[j];
		((uint8_t*)ptr)[j] ^= ((uint8_t*)ptr)[i];
		((uint8_t*)ptr)[i++] ^= ((uint8_t*)ptr)[j--];
	}
}
