/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multisplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:00:09 by pribault          #+#    #+#             */
/*   Updated: 2017/06/07 15:33:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_isof(int c, char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && c != str[i])
		i++;
	if (c == str[i])
		return (1);
	return (0);
}

char	**fill_multisplit(char **array, char *str, char *sep)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && ft_isof(str[i], sep))
			i++;
		l = 0;
		if (str[i] && !ft_isof(str[i], sep))
		{
			while (str[i + l] && !ft_isof(str[i + l], sep))
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

char	**ft_multisplit(char *str, char *sep)
{
	char	**array;
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (str[i])
	{
		while (str[i] && ft_isof(str[i], sep))
			i++;
		if (str[i] && !ft_isof(str[i], sep))
			l++;
		while (str[i] && !ft_isof(str[i], sep))
			i++;
	}
	if (!(array = (char**)malloc(sizeof(char*) * (l + 1))))
		return (NULL);
	return (fill_multisplit(array, str, sep));
}
