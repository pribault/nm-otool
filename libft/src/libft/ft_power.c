/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:29:47 by pribault          #+#    #+#             */
/*   Updated: 2017/07/25 12:04:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_power(long n, size_t power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	return (n * ft_power(n, power - 1));
}

double	ft_dpower(double n, size_t power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	return (n * ft_dpower(n, power - 1));
}
