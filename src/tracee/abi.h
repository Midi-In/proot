/* -*- c-set-style: "K&R"; c-basic-offset: 8 -*-
 *
 * This file is part of PRoot.
 *
 * Copyright (C) 2010, 2011, 2012 STMicroelectronics
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#ifndef TRACEE_ABI_H
#define TRACEE_ABI_H

#include <stdbool.h>

#include "tracee/info.h"
#include "tracee/reg.h"
#include "arch.h"
#include "notice.h"

enum abi {
	ABI_DEFAULT,
	ABI_2, /* x86_32 on x86_64.  */
	ABI_3, /* x32 on x86_64.  */
};

/**
 * Return the ABI currently used by the given @tracee.
 */
static inline enum abi get_abi(const struct tracee_info *tracee)
{
#if defined(ARCH_X86_64)
	switch (tracee->_regs.cache.cs) {
	case 0x23:
		return ABI_2;
	case 0x33:
	default:
		return ABI_DEFAULT;
	}
#else
	return ABI_DEFAULT;
#endif
}

/**
 * Return true if @tracee is a 32-bit process running on a 64-bit
 * kernel.
 */
static inline bool is_32on64_mode(const struct tracee_info *tracee)
{
	return (get_abi(tracee) != ABI_DEFAULT);
}

/**
 * Return the size of a word according to the ABI currently used by
 * the given @tracee.
 */
static inline size_t sizeof_word(const struct tracee_info *tracee)
{
	return (is_32on64_mode(tracee)
		? sizeof(word_t) / 2
		: sizeof(word_t));
}

#endif /* TRACEE_ABI_H */
