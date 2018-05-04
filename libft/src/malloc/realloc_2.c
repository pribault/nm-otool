/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:07:44 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 16:26:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	*lock_and_return(void *ptr)
{
	pthread_mutex_lock(&g_env.mutex);
	return (ptr);
}

void	*realloc_in_zones(t_zone *zone, void *ptr, size_t size)
{
	t_alloc	*prev;
	t_alloc	*alloc;

	while (zone)
	{
		if (ptr >= (void*)&zone[1] && ptr < (void*)&zone[1] + zone->size)
		{
			prev = NULL;
			alloc = get_in_zone(zone, &zone[1], sizeof(t_alloc));
			while (alloc)
			{
				if (ptr >= (void*)&alloc[1] &&
					ptr < (void*)&alloc[1] + alloc->size)
					return (realloc_in_zone(zone, prev, alloc, size));
				prev = alloc;
				alloc = get_in_zone(zone, (void*)&alloc[1] + alloc->size,
					sizeof(t_alloc));
			}
			return (NULL);
		}
		zone = zone->next;
	}
	return (NULL);
}

void	*try_reallocf(t_zone *zone, t_alloc *prev, t_alloc *alloc, size_t size)
{
	void	*result;

	if (!(result = realloc_in_zone(zone, prev, alloc, size)))
	{
		pthread_mutex_unlock(&g_env.mutex);
		free(&alloc[1]);
		pthread_mutex_lock(&g_env.mutex);
	}
	return (result);
}

void	*reallocf_in_zones(t_zone *zone, void *ptr, size_t size)
{
	t_alloc	*prev;
	t_alloc	*alloc;

	while (zone)
	{
		if (ptr >= (void*)&zone[1] && ptr < (void*)&zone[1] + zone->size)
		{
			prev = NULL;
			alloc = get_in_zone(zone, &zone[1], sizeof(t_alloc));
			while (alloc)
			{
				if (ptr >= (void*)&alloc[1] &&
					ptr < (void*)&alloc[1] + alloc->size)
					return (try_reallocf(zone, prev, alloc, size));
				prev = alloc;
				alloc = get_in_zone(zone, (void*)&alloc[1] + alloc->size,
					sizeof(t_alloc));
			}
			return (NULL);
		}
		zone = zone->next;
	}
	return (NULL);
}
