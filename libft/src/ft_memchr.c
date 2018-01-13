/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:12:35 by pribault          #+#    #+#             */
/*   Updated: 2016/11/10 16:20:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n - 1 && ((unsigned char*)s)[i] != (unsigned char)c)
		i++;
	if (((unsigned char*)s)[i] == (unsigned char)c)
		return ((char*)s + i);
	else
		return (NULL);
}
