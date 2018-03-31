/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:42:40 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 19:48:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

/*
****************
**	includes  **
****************
*/

# include <mach-o/ranlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <ar.h>

# include "libft.h"

/*
***************
**	defines  **
***************
*/

# define MACH_ENDIAN	BYTE(0)
# define FAT_ENDIAN		BYTE(1)
# define DEBUG			BYTE(2)
# define TEXT_SECTION	BYTE(3)
# define DATA_SECTION	BYTE(4)
# define BSS_SECTION	BYTE(5)
# define ENDIAN(x)		(x & MACH_ENDIAN)

# define STR_MAX		128

# define SAVE_LINE		8192

/*
*************
**	enums  **
*************
*/

typedef enum	e_otool_error
{
	ERROR_FSTAT = ERROR_FT_MAX,
	ERROR_MUNMAP,
	ERROR_UNKNOWN_FILE_FORMAT,
	ERROR_FILE_CORRUPTED,
	ERROR_ON_FD,
	ERROR_EMPTY_FILE,
	ERROR_OTOOL_MAX
}				t_otool_error;

typedef enum	e_ret
{
	RETURN_SUCCESS,
	RETURN_UNKNOWN_FILE_FORMAT = ERROR_UNKNOWN_FILE_FORMAT,
	RETURN_FILE_CORRUPTED = ERROR_FILE_CORRUPTED
}				t_ret;

typedef enum	e_file_type
{
	TYPE_AR,
	TYPE_MACH,
	TYPE_FAT,
}				t_file_type;

/*
******************
**	structures  **
******************
*/

typedef struct	s_otool
{
	t_vector	files;
	void		*ptr;
	size_t		size;
	t_vector	segment_32;
	t_vector	segment_64;
	uint8_t		opt;
	int			out;
	int			null;
	int			pipe[2];
	void		*buffer;
	size_t		buffer_size;
}				t_otool;

/*
******************
**	prototypes  **
******************
*/

/*
**	flags functions
*/

void			print_usage(void);
void			set_debug(t_otool *otool);
void			get_default(char *file, t_otool *otool);
void			set_text_section(t_otool *otool);
void			set_data_section(t_otool *otool);
void			set_bss_section(t_otool *otool);

/*
**	output functions
*/

void			clean_output(t_otool *otool);
void			save_output(t_otool *otool);
void			print_output(t_otool *otool);
void			print_output_to(t_otool *otool, int fd);

/*
**	get functions
*/

void			*get_prot(t_otool *otool, void *ptr, size_t size);
char			*get_str(t_otool *otool, char *ptr);
void			*get_fat_header(t_otool *otool, struct fat_header *ptr);
void			*get_fat_arch(t_otool *otool, struct fat_arch *ptr);
void			*get_fat_arch_64(t_otool *otool, struct fat_arch_64 *ptr);
void			*get_mach_header(t_otool *otool, struct mach_header *ptr);
void			*get_mach_header_64(t_otool *otool,
				struct mach_header_64 *ptr);
void			*get_load_command(t_otool *otool, struct load_command *ptr);
void			*get_segment_command(t_otool *otool,
				struct segment_command *ptr);
void			*get_segment_command_64(t_otool *otool,
				struct segment_command_64 *ptr);
void			*get_section(t_otool *otool, struct section *ptr);
void			*get_section_64(t_otool *otool, struct section_64 *ptr);
char			*get_cpu_type(cpu_type_t type);

/*
**	file reading functions
*/

t_ret			read_ar(t_otool *otool, void *ptr, char *name);
t_ret			read_fat(t_otool *otool, void *ptr, char *name);
t_ret			read_mach(t_otool *otool, void *ptr, char *name,
				t_file_type type);
t_ret			read_segment(t_otool *otool, void *ptr);
t_ret			read_segment_64(t_otool *otool, void *ptr);
t_ret			print_section_32(t_otool *otool, struct section *section,
				void *ptr, uint32_t size);
t_ret			print_section_32_endian(t_otool *otool,
				struct section *section, void *ptr, size_t size);
t_ret			print_section_64(t_otool *otool,
				struct section_64 *section, void *ptr, uint64_t size);
t_ret			print_section_64_endian(t_otool *otool,
				struct section_64 *section, void *ptr, size_t size);

char			*get_name(char *file);

/*
**	others
*/

void			endian(void *ptr, size_t size);

#endif
