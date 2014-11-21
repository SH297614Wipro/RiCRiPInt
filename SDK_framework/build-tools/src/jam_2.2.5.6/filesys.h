/*
 * Copyright 1993, 1995 Christopher Seiwald.
 *
 * This file is part of Jam - see jam.c for Copyright information.
 */

/*
 * filesys.h - FILENAME struct and OS specific file routines 
 */

# ifdef FATFS
# include "timestam.h"
# else
# include "timestamp.h"
# endif

/*
 * FILENAME - a name of a file, broken into <grist>dir/base/suffix(member)
 *
 * <grist> is salt to distinguish between targets that otherwise would
 * have the same name:  it never appears in the bound name of a target.
 * (member) is an archive member name: the syntax is arbitrary, but must 
 * agree in file_parse(), file_build() and the Jambase.
 *
 * On VMS, we keep track of whether the original path was a directory
 * (without a file), so that $(VAR:D) can climb to the parent.
 */

typedef struct _filename FILENAME;

struct _filename {
	struct filepart {
		char	*ptr;
		int	len;
	} part[6];
# define f_grist	part[0]
# define f_root		part[1]
# define f_dir		part[2]
# define f_base		part[3]
# define f_suffix	part[4]
# define f_member	part[5]

# ifdef VMS
	int		parent;
# endif

} ;

void file_parse();
void file_build();
void file_parent();

void file_archscan();

typedef void (*dirscan_func_t)(char *, int, timestamp_t);
void file_dirscan(char *, dirscan_func_t);

int file_time(char *, timestamp_t *);
