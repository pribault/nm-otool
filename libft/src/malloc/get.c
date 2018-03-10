/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 10:33:03 by pribault          #+#    #+#             */
/*   Updated: 2018/03/09 20:22:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	*get_in_zone(t_zone *zone, void *ptr, size_t size)
{
	if (!zone || ptr < (void*)&zone[1] ||
		ptr + size > (void*)&zone[1] + zone->size)
		return (NULL);
	return (ptr);
}
