/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circ_buffer_dequeue.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 08:26:43 by pribault          #+#    #+#             */
/*   Updated: 2018/03/27 08:43:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_circ_buffer_dequeue(t_circ_buffer *buffer)
{
	void	*result;

	if (buffer->read_idx == buffer->write_idx)
		return (NULL);
	result = buffer->ptr + buffer->read_idx * buffer->type;
	buffer->read_idx = (buffer->read_idx + 1) % buffer->elems;
	buffer->n--;
	return (result);
}
