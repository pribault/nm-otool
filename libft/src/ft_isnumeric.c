/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:31:16 by pribault          #+#    #+#             */
/*   Updated: 2018/02/01 10:31:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	return 0 if not a number;
**	return 1 if signed integer
**	return 2 if unsigned integer
**	return 3 if floating point number
*/

int	ft_isnumeric(char *s)
{
	int		type;
	int		i;

	i = 0;
	type = 2;
	while (s[i] && s[i] > 8 && s[i] < 14)
		i++;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
	{
		type = 1;
		i++;
	}
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			if (s[i] != '.' || type == 3)
				return (0);
			type = 3;
		}
		i++;
	}
	return (type);
}
