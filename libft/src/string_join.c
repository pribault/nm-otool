/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:06:03 by pribault          #+#    #+#             */
/*   Updated: 2018/02/01 18:42:03 by pribault         ###   ########.fr       */
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
	if (!(s = va_arg(va, char*)))
		s = "(null)";
	while (s[i])
		new[(*j)++] = s[i++];
}

size_t	get_string_len(va_list va)
{
	char	*s;

	if (!(s = va_arg(va, char*)))
		s = "(null)";
	return (ft_strlen(s));
}
