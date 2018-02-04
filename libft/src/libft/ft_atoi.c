/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:42:02 by pribault          #+#    #+#             */
/*   Updated: 2017/09/01 02:57:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char *str)
{
	int		negative;
	int		number;
	int		i;

	negative = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
		negative = 44 - str[i++];
	while (str[i] < 58 && str[i] > 47)
		number = number * 10 + str[i++] - 48;
	return (number * negative);
}

int		ft_atoi_base(char *str, char *base)
{
	char	*c;
	int		negative;
	int		number;
	int		len;
	int		i;

	negative = 1;
	number = 0;
	len = ft_strlen(base);
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
		negative = 44 - str[i++];
	while ((c = ft_strchr(base, str[i++])) && ft_strncmp(c, "\0", 1))
		number = number * len + c - base;
	return (number * negative);
}
