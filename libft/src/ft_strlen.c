/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:39:19 by pribault          #+#    #+#             */
/*   Updated: 2017/10/11 18:33:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t		ft_wstrlen(const wchar_t *s)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		if (s[i] <= 0x7F)
			l += 1;
		else if (s[i] <= 0x7FF)
			l += 2;
		else if (s[i] <= 0xFFFF)
			l += 3;
		else
			l += 4;
		i++;
	}
	return (l);
}
