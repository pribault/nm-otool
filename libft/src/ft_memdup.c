/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 16:13:54 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 16:22:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void *ptr, size_t size)
{
	void	*new;

	if (!ptr || !(new = malloc(size)))
		return (NULL);
	ft_memcpy(new, ptr, size);
	return (ptr);
}
