/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:22:33 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 14:46:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_implode(char **array, char c)
{
	size_t	size;
	size_t	i;
	char	*s;

	if (!array)
		return (NULL);
	size = 0;
	i = (size_t)-1;
	while (array[++i])
		size += ft_strlen(array[i]);
	if (!size)
		return (ft_strdup(""));
	if (!(s = malloc(sizeof(char) * (size + ft_arraylen(array)))))
		return (NULL);
	size = 0;
	i = (size_t)-1;
	while (array[++i])
	{
		ft_memcpy(s + size + i, array[i], ft_strlen(array[i]));
		size += ft_strlen(array[i]);
		s[size + i] = c;
	}
	s[size + i - 1] = '\0';
	return (s);
}
