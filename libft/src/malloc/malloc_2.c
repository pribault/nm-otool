/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 13:54:23 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 13:55:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	*reallocf(void *ptr, size_t size)
{
	void	*result;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_env.mutex);
	malloc_log(LOG_REALLOCF_REQUEST, (uint64_t)ptr, size);
	if (!(result = reallocf_in_zones(g_env.tiny, ptr, size)) &&
		!(result = reallocf_in_zones(g_env.small, ptr, size)) &&
		!(result = reallocf_in_zones(g_env.large, ptr, size)))
	{
		malloc_error(ERROR_INVALID_POINTER, ptr);
		return (unlock_and_return(LOG_REALLOCF_RETURN, NULL));
	}
	return (unlock_and_return(LOG_REALLOCF_RETURN, result));
}

void	*valloc(size_t size)
{
	if (!size)
		return (NULL);
	pthread_mutex_lock(&g_env.mutex);
	malloc_log(LOG_VALLOC_REQUEST, 0, size);
	if (!g_env.large)
		return (unlock_and_return(LOG_VALLOC_RETURN,
		get_allocation(g_env.large = create_zone(size, "LARGE"), size)));
		return (unlock_and_return(LOG_VALLOC_RETURN,
		allocate_large(g_env.large, size)));
}
