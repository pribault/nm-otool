/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circ_buffer_enqueue.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 08:26:43 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 12:48:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_circ_buffer_enqueue(t_circ_buffer *buffer, void *data)
{
	ft_memcpy(buffer->ptr + buffer->write_idx * buffer->type, data,
	buffer->type);
	buffer->write_idx = (buffer->write_idx + 1) % buffer->elems;
	buffer->write_idx %= buffer->elems;
	if (buffer->write_idx == buffer->read_idx)
	{
		if (buffer->trash_callback)
			buffer->trash_callback(buffer->data, buffer->ptr +
			buffer->read_idx * buffer->type);
		buffer->read_idx = (buffer->read_idx + 1) % buffer->elems;
	}
	else
		buffer->n++;
}
