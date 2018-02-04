/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:41:12 by pribault          #+#    #+#             */
/*   Updated: 2017/01/25 02:59:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(void **array, size_t len)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (i < len)
		free(array[i++]);
	free(array);
}
