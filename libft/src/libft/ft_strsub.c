/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:18:33 by pribault          #+#    #+#             */
/*   Updated: 2016/11/09 18:04:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (s == NULL)
		return (NULL);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result = ft_memcpy(result, s + start, len);
	result[len] = '\0';
	return (result);
}
