/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:47:40 by pribault          #+#    #+#             */
/*   Updated: 2017/05/12 17:49:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

static int	ft_printj_2(char *new)
{
	size_t	len;

	ft_putstr(new);
	len = ft_strlen(new);
	free(new);
	return (len);
}

int			ft_printj(const char *format, ...)
{
	char	*new;
	va_list	va;
	size_t	len;
	size_t	n;
	size_t	i;

	i = 0;
	n = 0;
	len = 0;
	va_start(va, format);
	while (format[i])
	{
		if (format[i++] == '%')
		{
			n++;
			len += get_next_arg(va, format, &i);
		}
	}
	new = (char*)malloc(sizeof(char) * (len + i - 2 * n + 1));
	ft_bzero(new, len + i - 2 * n + 1);
	va_start(va, format);
	fill_string(va, format, new);
	va_end(va);
	return (ft_printj_2(new));
}
