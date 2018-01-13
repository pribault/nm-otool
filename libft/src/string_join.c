/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:06:03 by pribault          #+#    #+#             */
/*   Updated: 2017/07/17 20:36:51 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

void	print_char_join(va_list va, char *new, size_t *j)
{
	char	c;

	c = va_arg(va, int);
	new[(*j)++] = c;
}

void	print_string(va_list va, char *new, size_t *j)
{
	size_t	i;
	char	*s;

	i = 0;
	s = va_arg(va, char*);
	while (s[i])
		new[(*j)++] = s[i++];
}

size_t	get_string_len(va_list va)
{
	return (ft_strlen(va_arg(va, char*)));
}
