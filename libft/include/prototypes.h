/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:34:59 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 12:07:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "libft.h"
# include "malloc.h"
# include "structs.h"
# include <sys/mman.h>

void	malloc_error(int error, void *param);
void	*unlock_and_return(t_log_type type, void *ptr);
void	*lock_and_return(void *ptr);

void	*allocate_large(t_zone *zone, size_t size);

t_zone	*create_zone(size_t size, char *name);
void	*allocate_in_zone(t_zone *zone, size_t size);

void	*get_in_zone(t_zone *zone, void *ptr, size_t size);
void	*get_allocation(t_zone *zone, size_t size);

void	claim_allocation(t_alloc *alloc, size_t size);

void	*realloc_in_zones(t_zone *zone, void *ptr, size_t size);
void	*reallocf_in_zones(t_zone *zone, void *ptr, size_t size);
void	*realloc_in_zone(t_zone *zone, t_alloc *prev, t_alloc *alloc,
		size_t size);
t_bool	free_in_zones(t_zone *zone, void *ptr);
t_bool	free_in_zone(t_zone *zone, void *ptr);

void	malloc_log(t_log_type type, uint64_t ptr, uint64_t size);

#endif
