/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:50:56 by pribault          #+#    #+#             */
/*   Updated: 2018/02/25 16:21:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char		*get_name(char *file)
{
	static char	name[17];
	size_t		i;

	i = 16;
	name[16] = '\0';
	while (--i != (size_t)-1)
	{
		if (file[i] == ' ')
			name[i] = '\0';
		else
			name[i] = file[i];
	}
	return ((char*)&name);
}

static t_ret	read_file_in_ar(char *lib, char *file, t_nm *nm)
{
	t_ret		ret;

	if (!strcmp(file, SYMDEF_SORTED) || !strcmp(file, SYMDEF))
		return (RETURN_SUCCESS);
	ft_printf("\n%s(%s):\n", lib, file);
	if (!file)
		return (RETURN_FILE_CORRUPTED);
	if ((ret = read_fat(nm, nm->ptr, file)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	if ((ret = read_mach(nm, nm->ptr, file, TYPE_MACH)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	if ((ret = read_ar(nm, nm->ptr, file)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	return (RETURN_UNKNOWN_FILE_FORMAT);
}

t_ret	read_ar(t_nm *nm, void *ptr, char *name)
{
	struct ar_hdr	*header;
	char			*ar;
	void			*save_ptr;
	size_t			save_size;

	if (!(ar = get_prot(nm, ptr, SARMAG)) ||
		strncmp(ar, ARMAG, SARMAG))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	ptr += SARMAG;
	save_ptr = nm->ptr;
	save_size = nm->size;
	while ((header = get_prot(nm, ptr, sizeof(struct ar_hdr))))
	{
		if (strncmp(&header->ar_fmag, ARFMAG, 2) ||
			!get_prot(nm, (void*)header + sizeof(struct ar_hdr),
			ft_atou(&header->ar_size)))
			return (RETURN_FILE_CORRUPTED);
		if (!strncmp(&header->ar_name, "#1/", 3))
		{
			nm->ptr = (void*)header + sizeof(struct ar_hdr) +
			ft_atou((void*)(&header->ar_name) + 3);
			nm->size = save_ptr + save_size - nm->ptr;
			read_file_in_ar(name, (void*)header + sizeof(struct ar_hdr), nm);
		}
		else
		{
			nm->ptr = (void*)header + sizeof(struct ar_hdr);
			nm->size = save_ptr + save_size - nm->ptr;
			read_file_in_ar(name, get_name(&header->ar_name), nm);
		}
		nm->ptr = save_ptr;
		nm->size = save_size;
		ptr += sizeof(struct ar_hdr) + ft_atou(&header->ar_size);
	}
	return (RETURN_SUCCESS);
}
