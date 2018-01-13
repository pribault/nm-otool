/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:40:26 by pribault          #+#    #+#             */
/*   Updated: 2016/11/09 16:47:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;
	size_t	size_src;
	size_t	size_dst;

	i = 0;
	j = ft_strlen(dst);
	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	while (i + j < size - 1 && src[i] && size)
	{
		dst[i + j] = src[i];
		i++;
	}
	dst[i + j] = '\0';
	if (size > size_dst)
		return (size_src + size_dst);
	else
		return (size_src + size);
}
