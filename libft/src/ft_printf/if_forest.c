/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_forest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:40:28 by pribault          #+#    #+#             */
/*   Updated: 2017/01/13 17:38:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_check(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D')
		return (1);
	if (c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U')
		return (1);
	if (c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

int		ft_check2(char c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (1);
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	if (c == '#' || c == '+' || c == '-' || c == ' ')
		return (1);
	return (0);
}

int		if_valid(const char *f, int i)
{
	while (ft_check2(f[i]))
		i++;
	if (ft_check(f[i]))
		return (1);
	return (0);
}

int		if_forest_two(va_list va, t_param param, const char *format, int *i)
{
	int		len;

	len = 0;
	if (format[*i] == 'u' || format[*i] == 'U')
	{
		if (format[*i] == 'U')
			param.modif = 0x1000;
		if_forest_unsigned(va, param, &len, "0123456789");
	}
	else if (format[*i] == 'p')
		if_forest_pointer(va, param, &len);
	else if (format[*i] == '%')
		if_forest_char(va, param, &len, '%');
	else if (format[*i] == 'O')
		if_forest_long(va, param, &len, "01234567");
	else if (format[*i] == 'D')
		if_forest_long(va, param, &len, "0123456789");
	else if (format[*i])
		len += print_wchar(format[*i]);
	else
		(*i)--;
	return (len);
}

int		if_forest_one(va_list va, const char *format, int *i)
{
	t_param		param;
	int			len;

	if (!if_valid(format, *i))
		return (0);
	(*i)++;
	len = 0;
	param = if_forest_param(format, i);
	if (format[*i] == 's' || format[*i] == 'S')
		if_forest_string(va, param, &len, format[*i]);
	else if (format[*i] == 'd' || format[*i] == 'i')
		if_forest_number(va, param, &len, "0123456789");
	else if (format[*i] == 'c')
		if_forest_char(va, param, &len, -2);
	else if (format[*i] == 'C')
		if_forest_char(va, param, &len, -1);
	else if (format[*i] == 'x')
		if_forest_unsigned(va, param, &len, "0123456789abcdef");
	else if (format[*i] == 'X')
		if_forest_unsigned(va, param, &len, "0123456789ABCDEF");
	else if (format[*i] == 'o')
		if_forest_unsigned(va, param, &len, "01234567");
	else
		len += if_forest_two(va, param, format, i);
	return (len);
}
