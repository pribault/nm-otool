/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 00:02:10 by pribault          #+#    #+#             */
/*   Updated: 2018/04/29 12:18:53 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

size_t	get_unicode_len(va_list va)
{
	size_t	len;
	size_t	i;
	wchar_t	*s;

	if (!(s = va_arg(va, wchar_t*)))
		s = L"(null)";
	i = (size_t)-1;
	len = 0;
	while (s[++i])
		if (s[i] <= 0x7F)
			len++;
		else if (s[i] <= 0x7FF)
			len += 2;
		else if (s[i] <= 0xFFFF)
			len += 3;
		else
			len += 4;
	return (len);
}

size_t	print_unicode_char(char *s, wchar_t c)
{
	if (c <= 0x7F)
	{
		s[0] = c;
		return (1);
	}
	if (c <= 0x7FF)
	{
		s[0] = (c >> 6) + 0xC0;
		s[1] = (c & 0x3F) + 0x80;
		return (2);
	}
	if (c <= 0xFFFF)
	{
		s[0] = (c >> 12) + 0xE0;
		s[1] = ((c >> 6) & 0x3F) + 0x80;
		s[2] = (c & 0x3F) + 0x80;
		return (3);
	}
	s[0] = (c >> 18) + 0xF0;
	s[1] = ((c >> 12) & 0x3F) + 0x80;
	s[2] = ((c >> 6) & 0x3F) + 0x80;
	s[3] = (c & 0x3F) + 0x80;
	return (4);
}

void	print_unicode(va_list va, char *new, size_t *j)
{
	size_t	i;
	wchar_t	*s;

	if (!(s = va_arg(va, wchar_t*)))
		s = L"(null)";
	i = (size_t)-1;
	while (s[++i])
		*j += print_unicode_char(&new[*j], s[i]);
}
