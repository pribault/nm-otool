/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 13:06:04 by pribault          #+#    #+#             */
/*   Updated: 2017/11/18 11:02:04 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "structs.h"
#include "prototypes.h"

t_alloc	*find_alloc(t_alloc *alloc, void *ptr)
{
	while (alloc)
	{
		if (is_in_alloc(alloc, ptr))
			return (alloc);
		alloc = alloc->next;
	}
	return (NULL);
}

t_alloc	*find_alloc_in_zone(t_zone *zone, void *ptr)
{
	t_alloc	*alloc;

	while (zone)
	{
		if ((alloc = find_alloc(zone->allocs, ptr)))
			return (alloc);
		zone = zone->next;
	}
	return (NULL);
}

void	*realloc_alloc(t_alloc *alloc, size_t size)
{
	void	*ret;

	if (size <= alloc->size || (alloc->next &&
	size < (size_t)(alloc->next->ptr - alloc->ptr)))
		alloc->size = size;
	else
	{
		ret = malloc(size);
		ft_memcpy(ret, alloc->ptr, (alloc->size < size) ? alloc->size : size);
		free(alloc->ptr);
		return (ret);
	}
	return (alloc->ptr);
}

void	*realloc_large(t_alloc *alloc, size_t size)
{
	if (!alloc)
		return (NULL);
	if (size <= alloc->size)
	{
		alloc->size = size;
		return (alloc->ptr);
	}
	free(alloc->ptr);
	return (malloc(size));
}

void	*realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;
	void	*ret;

	pthread_mutex_lock(&g_env.mutex[3]);
	ret = NULL;
	if (!ptr)
	{
		pthread_mutex_unlock(&g_env.mutex[3]);
		return (malloc(size));
	}
	alloc = find_alloc_in_zone(g_env.tiny, ptr);
	if (!alloc)
		alloc = find_alloc_in_zone(g_env.small, ptr);
	if (alloc)
		ret = realloc_alloc(alloc, size);
	else
		ret = realloc_large(find_alloc(g_env.large, ptr), size);
	pthread_mutex_unlock(&g_env.mutex[3]);
	return (ret);
}
