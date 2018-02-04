/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:39:25 by pribault          #+#    #+#             */
/*   Updated: 2016/11/05 15:30:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int			boolean;
	size_t		i;
	int			j;
	size_t		k;

	if (ft_strlen(little) == 0)
		return ((char*)big);
	boolean = 0;
	i = 0;
	while (boolean == 0 && big[i] && i <= len)
	{
		boolean = 1;
		j = 0;
		k = i;
		while (boolean == 1 && little[j] && k <= len)
			if (big[k++] != little[j++] || k > len)
				boolean = 0;
		i++;
	}
	if (boolean == 1)
		return ((char*)big + i - 1);
	else
		return (NULL);
}
