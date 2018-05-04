/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memschr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 10:59:02 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 17:58:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memschr(const void *big, const void *little, size_t n1, size_t n2)
{
	t_bool	valid;
	size_t	i;
	size_t	j;

	if (!n1 || n1 < n2)
		return (NULL);
	if (!n2)
		return ((void*)big);
	i = (size_t)-1;
	while (++i <= n1 - n2)
	{
		j = (size_t)-1;
		valid = FT_TRUE;
		while (++j < n2 && valid == FT_TRUE)
		{
			if (((uint8_t*)big)[i + j] != ((uint8_t*)little)[j])
				valid = FT_FALSE;
		}
		if (valid == FT_TRUE)
			return ((uint8_t*)big + i);
	}
	return (NULL);
}
