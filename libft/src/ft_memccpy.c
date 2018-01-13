/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:25:01 by pribault          #+#    #+#             */
/*   Updated: 2016/11/10 16:52:21 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char*)src)[i] != (unsigned char)c)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		((char*)dst)[i] = ((char*)src)[i];
		return (dst + i + 1);
	}
}
