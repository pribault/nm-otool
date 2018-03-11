/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:40:44 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 18:38:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unsigned_base(unsigned long long int n, int *l, char *bs, int b)
{
	if (n >= (unsigned int)b)
	{
		print_unsigned_base(n / b, l, bs, b);
		print_unsigned_base(n % b, l, bs, b);
	}
	else
		(*l) += print_char(bs[n]);
}

size_t	unsigned_len(unsigned long long int nbr, unsigned int base)
{
	size_t			len;

	len = 1;
	while (nbr >= base)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

void	ifu2(unsigned long long int n, t_param p, int *len, char *b)
{
	int	l;

	l = unsigned_len(n, ft_strlen(b));
	p.field = (ft_abs(p.field) < p.prec) ? l : p.field;
	if (p.hash && n != 0)
	{
		l += (!ft_strcmp("0123456789abcdef", b)) ? 2 : 0;
		l += (!ft_strcmp("0123456789ABCDEF", b)) ? 2 : 0;
		l += (!ft_strcmp("01234567", b)) ? 1 : 0;
	}
	*len += print_params(&p, l, ' ', 2);
	if (!ft_strcmp("0123456789abcdef", b) && p.hash && n != 0)
		print_str("0x", len, 2);
	if (!ft_strcmp("0123456789ABCDEF", b) && p.hash && n != 0)
		print_str("0X", len, 2);
	if (!ft_strcmp("01234567", b) && p.hash && n != 0)
		print_str("0", len, 1);
	*len += print_params(&p, l, '0', 2);
	*len += print_params(&p, l, '0', 1);
	print_unsigned_base(n, len, b, ft_strlen(b));
	*len += print_params(&p, l, '0', -1);
}

void	ifu3(t_param p, int *len)
{
	int	l;

	l = 0;
	p.field = (p.less) ? -p.field : p.field;
	*len += print_params(&p, l, '0', 1);
	*len += print_params(&p, l, ' ', 2);
	*len += print_params(&p, l, '0', 2);
	*len += print_params(&p, l, '0', -1);
}

void	if_forest_unsigned(va_list va, t_param p, int *len, char *base)
{
	unsigned long long int	nbr;

	if (p.modif == MODIF_HH)
		nbr = (unsigned char)va_arg(va, unsigned int);
	else if (p.modif == MODIF_H)
		nbr = (unsigned short)va_arg(va, unsigned int);
	else if (p.modif == MODIF_LL)
		nbr = (unsigned long long int)va_arg(va, unsigned long long int);
	else if (p.modif == MODIF_L)
		nbr = (unsigned long int)va_arg(va, unsigned long int);
	else if (p.modif == MODIF_J)
		nbr = (uintmax_t)va_arg(va, uintmax_t);
	else if (p.modif == MODIF_Z)
		nbr = (size_t)va_arg(va, size_t);
	else
		nbr = (unsigned int)va_arg(va, unsigned int);
	if (p.bool == 1 && p.prec == 0 && nbr == 0)
	{
		if (!p.hash || ft_strcmp("01234567", base))
			ifu3(p, len);
		else
			ifu2(nbr, p, len, base);
	}
	else
		ifu2(nbr, p, len, base);
}
