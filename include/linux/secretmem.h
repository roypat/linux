/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LINUX_SECRETMEM_H
#define _LINUX_SECRETMEM_H

#ifdef CONFIG_SECRETMEM

extern const struct address_space_operations secretmem_aops;

static inline bool secretmem_mapping(struct address_space *mapping)
{
	return mapping->flags & AS_INACCESSIBLE;
}

static inline bool vma_is_secretmem(struct vm_area_struct *vma)
{
	struct file *file = vma->vm_file;

	if (!file)
		return false;

	return secretmem_mapping(file->f_inode->i_mapping);
}

bool secretmem_active(void);

#else

static inline bool vma_is_secretmem(struct vm_area_struct *vma)
{
	return false;
}

static inline bool secretmem_mapping(struct address_space *mapping)
{
	return false;
}

static inline bool secretmem_active(void)
{
	return false;
}

#endif /* CONFIG_SECRETMEM */

#endif /* _LINUX_SECRETMEM_H */
