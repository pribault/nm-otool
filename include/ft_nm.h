/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:41:36 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 00:28:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

/*
****************
**	includes  **
****************
*/

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "libft.h"

/*
***************
**	defines  **
***************
*/

# define ENDIAN	BYTE(0)

/*
*************
**	enums  **
*************
*/

typedef enum	e_nm_error
{
	ERROR_FSTAT = ERROR_FT_MAX,
	ERROR_MUNMAP,
	ERROR_UNKNOWN_FILE_FORMAT,
	ERROR_NM_MAX
}				t_nm_error;

/*
******************
**	structures  **
******************
*/

typedef struct	s_nm
{
	void		*ptr;
	size_t		size;
	size_t		n;
	uint8_t		opt;
}				t_nm;

/*
******************
**	prototypes  **
******************
*/

/*
**	flag functions
*/

void			print_usage(void);
void			get_file(char *file, t_nm *nm);

/*
**	memory functions
*/

void			*get_prot(t_nm *nm, void *ptr, size_t size);
void			*get_fat_header(t_nm *nm, struct fat_header *ptr);
void			*get_fat_arch(t_nm *nm, struct fat_arch *ptr);
void			*get_fat_arch_64(t_nm *nm, struct fat_arch_64 *ptr);

/*
**	endian functions
*/

void			endian(void *ptr, size_t size);
void			*endian_mach_header(struct mach_header *ptr);
void			*endian_mach_header_64(struct mach_header_64 *ptr);

/*
**	read functions
*/

int				read_fat(t_nm *nm, void *ptr);
int				read_mach(t_nm *nm, void *ptr);
int				read_ar(t_nm *nm, void *ptr);


#endif
