/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:18:45 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 17:03:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static int	check_zone(t_zone *zone)
{
	uint64_t	size;
	t_alloc		*alloc;

	while (zone)
	{
		size = 0;
		alloc = get_in_zone(zone, &zone[1], sizeof(t_alloc));
		while (alloc)
		{
			size += (sizeof(t_alloc) + alloc->size);
			alloc = get_in_zone(zone, (void*)&alloc[1] + alloc->size,
				sizeof(t_alloc));
		}
		if (zone->size != size)
		{
			pthread_mutex_unlock(&g_env.mutex);
			return (MALLOC_CORRUPTED);
		}
		zone = zone->next;
	}
	return (MALLOC_OK);
}

int			check_malloc(void)
{
	int	ret;

	pthread_mutex_lock(&g_env.mutex);
	if ((ret = check_zone(g_env.tiny)) != MALLOC_OK)
		return (ret);
	if ((ret = check_zone(g_env.small)) != MALLOC_OK)
		return (ret);
	if ((ret = check_zone(g_env.large)) != MALLOC_OK)
		return (ret);
	pthread_mutex_unlock(&g_env.mutex);
	return (MALLOC_OK);
}
