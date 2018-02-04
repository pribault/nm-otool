/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:41:57 by pribault          #+#    #+#             */
/*   Updated: 2017/09/01 07:21:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		*fill_itoa(char *result, int negative[2], int n, long i[2])
{
	i[2] = 0;
	if (negative[0] == 1)
		result[i[2]++] = '-';
	while (i[0] >= 1)
	{
		result[i[2]++] = 48 + n / i[0];
		n = n - (n / i[0]) * i[0];
		i[0] /= 10;
		if (i[0] == 1 && negative[1] == 1)
			n++;
	}
	result[i[2]] = '\0';
	return (result);
}

char			*ft_itoa(int n)
{
	char	*result;
	long	i[3];
	int		negative[2];

	negative[0] = 0;
	negative[1] = 0;
	i[0] = 1;
	i[1] = 1;
	if (n < 0)
	{
		if (n == -2147483648)
			negative[1] = 1;
		negative[0] = 1;
		n = -n - negative[1];
	}
	while (i[0] * 10 <= n)
	{
		i[0] *= 10;
		i[1]++;
	}
	result = (char*)malloc(sizeof(char) * (i[1] + negative[0] + 1));
	if (result == NULL)
		return (NULL);
	return (fill_itoa(result, negative, n, i));
}

char			*ft_itoa_base(int n, char *base)
{
	int		b;
	int		i;
	char	*result;
	char	neg;
	char	len;

	neg = (n < 0) ? 1 : 0;
	len = 1;
	b = ft_strlen(base);
	while (ft_power(b, len) <= ((neg) ? -(long)n : n))
		len++;
	if (!(result = (char*)malloc(sizeof(char) * (len + neg + 1))))
		return (NULL);
	i = 0;
	if (neg)
		result[i++] = '-';
	while (len > 0)
	{
		result[i++] = base[ft_abs(n / ft_power(b, len - 1))];
		n = n % ft_power(b, len - 1);
		len--;
	}
	result[i] = '\0';
	return (result);
}
