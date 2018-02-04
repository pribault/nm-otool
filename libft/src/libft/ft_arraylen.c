/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 12:30:44 by pribault          #+#    #+#             */
/*   Updated: 2016/11/22 12:32:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraylen(char **array)
{
	int		len;

	len = 0;
	if (!array)
		return (0);
	while (array[len])
		len++;
	return (len);
}
