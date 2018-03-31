/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circ_buffer_set_trash_callback.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 11:49:16 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 12:48:29 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_circ_buffer_set_trash_callback(t_circ_buffer *buffer,
		void (*callback)(void*, void*), void *data)
{
	buffer->trash_callback = callback;
	buffer->data = data;
}
