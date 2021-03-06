/*
 * Arm inline-assembly
 *
 * (C) 2019.03.15 BuddyZhang1 <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/kernel.h>

/*
 * BPL ---> > 0 ---> N0nNegative number
 *
 * Syntax
 *   BPL <Branch>
 */

static int debug_bpl(void)
{
	unsigned long R1 = 0x8;
	unsigned long R2 = 0x2;
	unsigned long RET;

	/* BPL <branch> --> NoNegative number and jump to branck */
	__asm__ volatile ("cmp %1, %2\n\r"
			  "bpl _nng\n\r"
			  "mov %0, #0\n\r"
			  "b out\n\r"
		"_nng:\n\r"
			  "mov %0, #1\n\r"
		"out:\n\r"
			  "nop"
			: "=r" (RET)
			: "r" (R1), "r" (R2));

	if (RET)
		printk("%#lx - %#lx >= 0", R1, R2);
	else
		printk("%#lx - %#lx < 0", R1, R2);

	return 0;
}
device_initcall(debug_bpl);
