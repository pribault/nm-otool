/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:59:53 by pribault          #+#    #+#             */
/*   Updated: 2016/11/05 14:43:35 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		boolean;
	int		i;
	int		j;
	int		k;

	if (ft_strlen(little) == 0)
		return ((char*)big);
	boolean = 0;
	i = 0;
	while (boolean == 0 && big[i])
	{
		boolean = 1;
		j = 0;
		k = i;
		while (boolean == 1 && little[j])
		{
			if (big[k++] != little[j++])
				boolean = 0;
		}
		i++;
	}
	if (boolean == 1)
		return ((char*)big + i - 1);
	else
		return (NULL);
}
