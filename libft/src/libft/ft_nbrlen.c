/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 12:50:05 by pribault          #+#    #+#             */
/*   Updated: 2017/07/19 13:25:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(int nbr)
{
	size_t	len;

	len = (nbr < 0) ? 2 : 1;
	nbr = ft_abs(nbr);
	while (nbr / 10)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

size_t	ft_nbrlen_base(int nbr, int base)
{
	size_t	len;

	len = (nbr < 0) ? 2 : 1;
	nbr = ft_abs(nbr);
	while (nbr / base)
	{
		len++;
		nbr /= base;
	}
	return (len);
}
