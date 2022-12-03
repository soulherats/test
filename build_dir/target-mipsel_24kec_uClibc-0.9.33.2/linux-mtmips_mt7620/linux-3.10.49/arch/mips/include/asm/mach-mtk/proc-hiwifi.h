/*
 *  Turbo Wireless boards use create normol proc/hiwifi
 *
 *  Copyright (C) 2012-2013 allan
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#ifndef __PROC_HIWIFI_H
#define __PROC_HIWIFI_H

#include <linux/fs.h>

#define PROC_HIWIFI_NAME	"hiwifi"

struct proc_dir_entry *register_proc_hiwifi_entry(const char *name, mode_t mode, struct proc_dir_entry *parent, const struct file_operations *fops);
int unregister_proc_hiwifi_entry(const char *name, struct proc_dir_entry *parent);

struct proc_dir_entry *register_proc_hiwifi_dir(const char *name, struct proc_dir_entry *parent);
int unregister_proc_hiwifi_dir(const char *name, struct proc_dir_entry *parent);

void __init proc_hiwifi_init(void);

#endif 	/* __PROC_HIWIFI_H */
