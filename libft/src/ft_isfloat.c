/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:03:29 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 14:08:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isfloat(char *s)
{
	t_bool	boolean;
	int		i;

	i = 0;
	boolean = FT_FALSE;
	while (s[i] && s[i] > 8 && s[i] < 14)
		i++;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			if (s[i] != '.' || boolean)
				return (0);
			boolean = FT_TRUE;
		}
		i++;
	}
	return (boolean);
}
