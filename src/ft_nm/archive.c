/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:50:56 by pribault          #+#    #+#             */
/*   Updated: 2018/05/03 18:29:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_ret	read_file_in_ar(char *lib, char *file, t_nm *nm)
{
	t_ret		ret;

	if (!file)
		return (RETURN_FILE_CORRUPTED);
	if (!ft_strcmp(file, SYMDEF_SORTED) || !ft_strcmp(file, SYMDEF))
		return (RETURN_SUCCESS);
	ft_printf("\n%s(%s):\n", lib, file);
	if ((ret = read_fat(nm, nm->ptr, file)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	if ((ret = read_mach(nm, nm->ptr, file, TYPE_AR)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	if ((ret = read_ar(nm, nm->ptr, file)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	return (RETURN_UNKNOWN_FILE_FORMAT);
}

t_ret			restore_nm(t_nm *nm, void *ptr, size_t size, t_ret ret)
{
	nm->ptr = ptr;
	nm->size = size;
	return (ret);
}

static t_ret	read_ar_2(t_nm *nm, struct ar_hdr *header, char *name,
				uint64_t *save)
{
	nm->ptr = (void*)header + sizeof(struct ar_hdr) +
	ft_atou((void*)(&header->ar_name) + 3);
	nm->size = save[0] + save[1] - (uint64_t)nm->ptr;
	if (read_file_in_ar(name, (void*)header + sizeof(struct ar_hdr),
		nm) == RETURN_FILE_CORRUPTED)
		return (restore_nm(nm, (void*)save[0], save[1],
		RETURN_FILE_CORRUPTED));
		return (RETURN_SUCCESS);
}

static t_ret	read_ar_3(t_nm *nm, struct ar_hdr *header, char *name,
				uint64_t *save)
{
	nm->ptr = (void*)header + sizeof(struct ar_hdr);
	nm->size = save[0] + save[1] - (uint64_t)nm->ptr;
	if (read_file_in_ar(name, get_name((char*)&header->ar_name), nm))
		return (restore_nm(nm, (void*)save[0], save[1],
		RETURN_FILE_CORRUPTED));
		return (RETURN_SUCCESS);
}

/*
**	save[0]: pointer save
**	save[1]: size save
*/

t_ret			read_ar(t_nm *nm, void *ptr, char *name)
{
	struct ar_hdr	*header;
	char			*ar;
	uint64_t		save[2];

	if (!(ar = get_prot(nm, ptr, SARMAG)) ||
		ft_strncmp(ar, ARMAG, SARMAG))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	ptr += SARMAG;
	save[0] = (uint64_t)nm->ptr;
	save[1] = nm->size;
	while ((header = get_prot(nm, ptr, sizeof(struct ar_hdr))))
	{
		if (ft_strncmp((char*)&header->ar_fmag, ARFMAG, 2) ||
			!get_prot(nm, (void*)header + sizeof(struct ar_hdr),
			ft_atou((char*)&header->ar_size)))
			return (RETURN_FILE_CORRUPTED);
		if ((!ft_strncmp((char*)&header->ar_name, "#1/", 3) && read_ar_2(nm,
			header, name, (uint64_t*)&save) != RETURN_SUCCESS) ||
			(ft_strncmp((char*)&header->ar_name, "#1/", 3) && read_ar_3(nm,
			header, name, (uint64_t*)&save) != RETURN_SUCCESS))
			return (RETURN_FILE_CORRUPTED);
		restore_nm(nm, (void*)save[0], save[1], RETURN_SUCCESS);
		ptr += sizeof(struct ar_hdr) + ft_atou((char*)&header->ar_size);
	}
	return (RETURN_SUCCESS);
}
