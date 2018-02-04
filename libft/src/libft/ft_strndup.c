/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:08:10 by pribault          #+#    #+#             */
/*   Updated: 2017/02/15 14:40:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strndup(const char *str, size_t n)
{
	char	*new;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	if (len > n)
		len = n;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}
