/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 10:42:26 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 15:41:00 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	claim_allocation(t_alloc *alloc, size_t size)
{
	t_alloc	*next;

	alloc->type = TYPE_ALLOC;
	if (alloc->size - size >= sizeof(t_alloc))
	{
		next = (void*)&alloc[1] + size;
		next->type = TYPE_FREE;
		next->size = alloc->size - size - sizeof(t_alloc);
		alloc->size = size;
	}
}

void	*allocate_large(t_zone *zone, size_t size)
{
	if (!zone)
		return (NULL);
	if (((t_alloc*)&zone[1])->type == TYPE_FREE &&
		((t_alloc*)&zone[1])->size >= size)
		return (get_allocation(zone, size));
	while (zone->next)
	{
		if (((t_alloc*)&zone[1])->type == TYPE_FREE &&
			((t_alloc*)&zone[1])->size >= size)
			return (get_allocation(zone, size));
		zone = zone->next;
	}
	if (!(zone->next = create_zone(size, zone->name)))
		return (NULL);
	return (get_allocation(zone->next, size));
}
