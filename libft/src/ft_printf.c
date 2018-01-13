/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardanel <ardanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:39:57 by pribault          #+#    #+#             */
/*   Updated: 2017/03/14 09:23:56 by ardanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	va;
	int		len;
	int		i;

	i = 0;
	len = 0;
	va_start(va, format);
	while (format[i])
	{
		if (format[i] == '%')
			len += if_forest_one(va, format, &i);
		else
			len += print_char(format[i]);
		i++;
	}
	va_end(va);
	return (len);
}
