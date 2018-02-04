/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:36:47 by pribault          #+#    #+#             */
/*   Updated: 2016/11/09 18:06:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**fill_ft_strsplit(char const *s, char **result, char c)
{
	int		len;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i + len] != c && s[i + len])
				len++;
			result[y] = malloc(sizeof(char) * (len + 1));
			if (result[y] == NULL)
				return (NULL);
			result[y] = ft_memcpy(result[y], s + i, len);
			result[y++][len] = '\0';
			i += len;
		}
	}
	result[y] = NULL;
	return (result);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**result;
	int		i;
	int		y;

	if (s == NULL)
		return (NULL);
	i = 0;
	y = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			y++;
		while (s[i] != c && s[i])
			i++;
	}
	result = malloc(sizeof(char*) * (y + 1));
	if (result == NULL)
		return (NULL);
	return (fill_ft_strsplit(s, result, c));
}
