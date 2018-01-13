/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:18:11 by pribault          #+#    #+#             */
/*   Updated: 2017/06/16 15:25:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	int		negative;
	double	number;
	int		i;
	long	p;

	negative = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14) || str[i] == 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
		negative = 44 - str[i++];
	while (str[i] < 58 && str[i] > 47)
		number = number * 10 + str[i++] - 48;
	if (str[i] == '.')
		i++;
	p = 10;
	while (str[i] < 58 && str[i] > 47)
	{
		number += ((double)(str[i++] - 48) / p);
		p *= 10;
	}
	return (number * negative);
}
