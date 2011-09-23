/*
 * Copyright Red Hat, Inc. 2009
 *
 * Author:	Vivek Goyal <vgoyal@redhat.com>
 *		Jan Safranek <jsafrane@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __TOOLS_COMMON

#define __TOOLS_COMMON

#include "config.h"
#include <libcgroup.h>
#include <libcgroup-internal.h>

#ifdef CGROUP_DEBUG
#define cgroup_dbg(x...) printf(x)
#else
#define cgroup_dbg(x...) do {} while (0)
#endif

/**
 * Auxiliary specifier of group, used to store parsed command line options.
 */
struct cgroup_group_spec {
	char path[FILENAME_MAX];
	char *controllers[CG_CONTROLLER_MAX];
};


/**
 * Simple dynamic array of strings.
 */
struct cgroup_string_list {
	char **items;
	int size;
	int count;
};

/**
 * Parse command line option with group specifier into provided data structure.
 * The option must have form of 'controller1,controller2,..:group_name'.
 *
 * The parsed list of controllers and group name is added at the end of
 * provided cdptr, i.e. on place of first NULL cgroup_group_spec*.
 *
 * @param cdptr Target data structure to fill. New item is allocated and added
 * 		at the end.
 * @param optarg Argument to parse.
 * @param capacity Capacity of the cdptr array.
 * @return 0 on success, != 0 on error.
 */
int parse_cgroup_spec(struct cgroup_group_spec **cdptr, char *optarg,
		int capacity);

/**
 * Free a single cgroup_group_spec structure.
 * 	@param cl The structure to free from memory
 */
void cgroup_free_group_spec(struct cgroup_group_spec *cl);


/**
 * Initialize a new list.
 * @param list List to initialize.
 * @param initial_size Initial size of the list to pre-allocate.
 */
int cgroup_string_list_init(struct cgroup_string_list *list,
		int initial_size);

/**
 * Destroy a list, automatically freeing all its items.
 * @param list List to destroy.
 */
void cgroup_string_list_free(struct cgroup_string_list *list);

/**
 * Adds new item to the list. It automatically resizes underlying array if
 * needed.
 * @param list List to modify.
 * @param item Item to add. The item is automatically copied to new buffer.
 */
int cgroup_string_list_add_item(struct cgroup_string_list *list,
		const char *item);

/**
 * Add alphabetically sorted files present in given directory (without subdirs)
 * to list of strings. The function exits on error.
 * @param list The list to add files to.
 * @param dirname Full path to directory to examime.
 * @param program_name Name of the executable, it will be used for printing
 * errors to stderr.
 *
 */
int cgroup_string_list_add_directory(struct cgroup_string_list *list,
		char *dirname, char *program_name);


#endif /* TOOLS_COMMON */
