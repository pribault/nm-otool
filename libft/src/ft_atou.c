/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:09:28 by pribault          #+#    #+#             */
/*   Updated: 2017/06/16 15:11:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atou(char *str)
{
	unsigned int	number;
	int				i;

	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14) || str[i] == 0)
		i++;
	while (str[i] < 58 && str[i] > 47)
		number = number * 10 + str[i++] - 48;
	return (number);
}
