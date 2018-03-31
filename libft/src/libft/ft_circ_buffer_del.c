/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circ_buffer_del.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 19:37:42 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 17:29:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_circ_buffer_del(t_circ_buffer *buffer)
{
	if (buffer->alloc == ALLOC_MALLOC)
	{
		if (buffer->ptr)
			free(buffer->ptr);
	}
	else if (buffer->alloc == ALLOC_MMAP)
	{
		if (buffer->ptr)
			munmap(buffer->ptr, buffer->type * buffer->elems);
	}
	buffer->ptr = NULL;
	buffer->elems = 0;
	buffer->type = 0;
	buffer->write_idx = 0;
	buffer->read_idx = 0;
}
