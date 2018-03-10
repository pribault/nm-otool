/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 09:09:58 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 15:19:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	dump_zone(void *ptr, size_t size)
{
	char		*str;
	uint32_t	padding;
	size_t		i;

	if ((str = getenv("MALLOC_PADDING")))
		padding = ft_atou(str);
	else
		padding = DEFAULT_PADDING;
	i = (size_t)-1;
	ft_putchar('\n');
	while (++i < size)
	{
		if (!(i % padding))
			ft_putstr("\t");
		if (((i + 1) % padding))
			ft_printf("%s%.2hhx\e[0m ",
			(*(uint8_t*)(ptr + i)) ? g_env.colors[5] : g_env.colors[6],
			*(uint8_t*)(ptr + i));
		else
			ft_printf("%s%.2hhx\e[0m\n",
			(*(uint8_t*)(ptr + i)) ? g_env.colors[5] : g_env.colors[6],
			*(uint8_t*)(ptr + i));
	}
	ft_putstr((i % padding) ? "\n\n" : "\n");
}

void	show_zone(t_zone *zone)
{
	t_alloc	*alloc;

	alloc = get_in_zone(zone, &zone[1], sizeof(t_zone));
	ft_printf("%s%s\e[0m\t%s%p\e[0m %s-\e[0m %s%p\e[0m %s;\e[0m %lu bytes\n",
	g_env.colors[2], zone->name,
	g_env.colors[3], &zone[1],
	g_env.colors[1],
	g_env.colors[3], &zone[1] + zone->size - 1,
	g_env.colors[0], zone->size);
	while (alloc)
	{
		if (alloc->type == TYPE_ALLOC)
			ft_printf("\t%s%p\e[0m %s-\e[0m %s%p\e[0m %s;\e[0m %lu bytes\n",
			g_env.colors[4], &alloc[1],
			g_env.colors[1],
			g_env.colors[4], &alloc[1] + alloc->size - 1,
			g_env.colors[0],
			alloc->size);
		alloc = get_in_zone(zone, (void*)&alloc[1] + alloc->size,
		sizeof(t_alloc));
	}
	ft_putchar('\n');
}

void	show_zone_ex(t_zone *zone)
{
	t_alloc	*alloc;

	alloc = (void*)&zone[1];
	ft_printf("%s%s\e[0m\t%s%p\e[0m %s-\e[0m %s%p\e[0m %s;\e[0m %lu bytes\n",
	g_env.colors[2], zone->name,
	g_env.colors[3], &zone[1],
	g_env.colors[1],
	g_env.colors[3], &zone[1] + zone->size - 1,
	g_env.colors[0], zone->size);
	while (alloc)
	{
		if (alloc->type == TYPE_ALLOC)
		{
			ft_printf("\t%s%p\e[0m %s-\e[0m %s%p\e[0m %s;\e[0m %lu bytes\n",
			g_env.colors[4], &alloc[1],
			g_env.colors[1],
			g_env.colors[4], &alloc[1] + alloc->size - 1,
			g_env.colors[0],
			alloc->size);
			dump_zone(&alloc[1], alloc->size);
		}
		alloc = get_in_zone(zone, (void*)&alloc[1] + alloc->size,
		sizeof(t_alloc));
	}
	ft_putchar('\n');
}

void	show_alloc_mem(void)
{
	t_zone	*zone;

	pthread_mutex_lock(&g_env.mutex);
	ft_putchar('\n');
	zone = g_env.tiny;
	while (zone)
	{
		show_zone(zone);
		zone = zone->next;
	}
	zone = g_env.small;
	while (zone)
	{
		show_zone(zone);
		zone = zone->next;
	}
	zone = g_env.large;
	while (zone)
	{
		show_zone(zone);
		zone = zone->next;
	}
	pthread_mutex_unlock(&g_env.mutex);
}

void	show_alloc_mem_ex(void)
{
	t_zone	*zone;

	pthread_mutex_lock(&g_env.mutex);
	ft_putchar('\n');
	zone = g_env.tiny;
	while (zone)
	{
		show_zone_ex(zone);
		zone = zone->next;
	}
	zone = g_env.small;
	while (zone)
	{
		show_zone_ex(zone);
		zone = zone->next;
	}
	zone = g_env.large;
	while (zone)
	{
		show_zone_ex(zone);
		zone = zone->next;
	}
	pthread_mutex_unlock(&g_env.mutex);
}
