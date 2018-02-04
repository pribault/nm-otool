/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isunsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:03:29 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 14:10:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isunsigned(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] > 8 && s[i] < 14)
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}
