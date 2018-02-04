/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 22:02:35 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 14:28:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	endian(void *ptr, size_t size)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		((uint8_t*)ptr)[i] ^= ((uint8_t*)ptr)[j];
		((uint8_t*)ptr)[j] ^= ((uint8_t*)ptr)[i];
		((uint8_t*)ptr)[i++] ^= ((uint8_t*)ptr)[j--];
	}
}

void	*endian_nlist(t_nm *nm, struct nlist *ptr)
{
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->n_un.n_strx, sizeof(uint32_t));
		endian(&ptr->n_type, sizeof(uint8_t));
		endian(&ptr->n_sect, sizeof(uint8_t));
		endian(&ptr->n_desc, sizeof(int16_t));
		endian(&ptr->n_value, sizeof(uint32_t));
	}
	return (ptr);
}

void	*endian_nlist_64(t_nm *nm, struct nlist_64 *ptr)
{
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->n_un.n_strx, sizeof(uint32_t));
		endian(&ptr->n_type, sizeof(uint8_t));
		endian(&ptr->n_sect, sizeof(uint8_t));
		endian(&ptr->n_desc, sizeof(uint16_t));
		endian(&ptr->n_value, sizeof(uint64_t));
	}
	return (ptr);
}
