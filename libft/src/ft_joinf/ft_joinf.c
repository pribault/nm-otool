/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:06:03 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 17:05:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

size_t		get_next_arg(va_list va, const char *format, size_t *i)
{
	if (format[*i] == 'd' || format[*i] == 'i')
		return (get_number_len(va, "0123456789"));
	else if (format[*i] == 'u')
		return (get_unsigned_len(va, "0123456789"));
	else if (format[*i] == 'x')
		return (get_number_len(va, "0123456789abcdef"));
	else if (format[*i] == 'p')
		return (get_pointer_len(va, "0123456789abcdef"));
	else if (format[*i] == 'o')
		return (get_number_len(va, "01234567"));
	else if (format[*i] == 'b')
		return (get_number_len(va, "01"));
	else if (format[*i] == 's')
		return (get_string_len(va));
	else if (format[*i] == 'c')
		return (1);
	return (0);
}

void		print_next_arg(va_list va, char *new, size_t *j, char c)
{
	if (c == 'd' || c == 'i')
		print_number(va, new, j, "0123456789");
	else if (c == 'x')
		print_number(va, new, j, "0123456789abcdef");
	else if (c == 'p')
		print_pointer(va, new, j);
	else if (c == 'o')
		print_number(va, new, j, "01234567");
	else if (c == 'b')
		print_number(va, new, j, "01");
	else if (c == 's')
		print_string(va, new, j);
	else if (c == 'c')
		print_char_join(va, new, j);
}

void		fill_string(va_list va, const char *format, char *new)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			print_next_arg(va, new, &j, format[i++]);
		}
		else
			new[j++] = format[i++];
	}
}

char		*ft_joinf(const char *format, ...)
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
	new = (char*)malloc(sizeof(char) * (len + i - n + 1));
	ft_bzero(new, len + i - n + 1);
	va_start(va, format);
	fill_string(va, format, new);
	va_end(va);
	return (new);
}
