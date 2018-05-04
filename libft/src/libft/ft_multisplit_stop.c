/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multisplit_stop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 12:27:42 by pribault          #+#    #+#             */
/*   Updated: 2018/04/07 12:31:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**fill_multisplit(char **array, char *str, char *sep, char *stop)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	while (str[i] && !ft_isof(str[i], stop))
	{
		while (str[i] && ft_isof(str[i], sep) && !ft_isof(str[i], stop))
			i++;
		l = 0;
		if (str[i] && !ft_isof(str[i], sep) && !ft_isof(str[i], stop))
		{
			while (str[i + l] && !ft_isof(str[i + l], sep) &&
				!ft_isof(str[i], stop))
				l++;
			if (!(array[j] = (char*)malloc(sizeof(char) * (l + 1))))
				return (NULL);
			ft_memcpy(array[j], str + i, l);
			array[j++][l] = '\0';
			i += l;
		}
	}
	array[j] = NULL;
	return (array);
}

char		**ft_multisplit_stop(char *str, char *sep, char *stop)
{
	char	**array;
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (str[i] && !ft_isof(str[i], stop))
	{
		while (str[i] && ft_isof(str[i], sep) && !ft_isof(str[i], stop))
			i++;
		if (str[i] && !ft_isof(str[i], sep) && !ft_isof(str[i], stop))
			l++;
		while (str[i] && !ft_isof(str[i], sep) && !ft_isof(str[i], stop))
			i++;
	}
	if (!(array = (char**)malloc(sizeof(char*) * (l + 1))))
		return (NULL);
	return (fill_multisplit(array, str, sep, stop));
}
