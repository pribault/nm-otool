/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:10:15 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 19:21:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char **env, char *name)
{
	size_t	len[2];
	size_t	i;

	if (!env || !name)
		return (NULL);
	i = ft_arraylen(env);
	len[0] = ft_strlen(name);
	while (--i != (size_t)-1)
	{
		len[1] = ft_strlen(env[i]);
		if (len[1] > len[0] &&
			!ft_strncmp(env[i], name, len[0]) &&
			env[i][len[0]] == '=')
			return (&env[i][len[0] + 1]);
	}
	return (NULL);
}
