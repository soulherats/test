/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * Parts of this file are based on Ralink's 2.6.21 BSP
 *
 * Copyright (C) 2008-2011 Gabor Juhos <juhosg@openwrt.org>
 * Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 * Copyright (C) 2013 John Crispin <blogic@openwrt.org>
 */

#ifndef _MT7621_REGS_H_
#define _MT7621_REGS_H_

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/types.h>
#include <linux/bitops.h>
#include <asm/addrspace.h>

#define MT7621_SYSC_BASE		0x1E000000

#define SYSC_REG_CHIP_NAME0		0x00
#define SYSC_REG_CHIP_NAME1		0x04
#define SYSC_REG_CHIP_REV		0x0c
#define SYSC_REG_SYSTEM_CONFIG0		0x10
#define SYSC_REG_SYSTEM_CONFIG1		0x14
#define SYSC_REG_GPIO_MDOE		0x60

#define CHIP_REV_PKG_MASK		0x1
#define CHIP_REV_PKG_SHIFT		16
#define CHIP_REV_VER_MASK		0xf
#define CHIP_REV_VER_SHIFT		8
#define CHIP_REV_ECO_MASK		0xf

#define SYSCFG0_DRAM_TYPE_MASK          0x3
#define SYSCFG0_DRAM_TYPE_SHIFT         4
#define SYSCFG0_DRAM_TYPE_DDR3          0
#define SYSCFG0_DRAM_TYPE_DDR2          1

#define MT7621_DRAM_BASE                0x0
#define MT7621_DDR2_SIZE_MIN		32
#define MT7621_DDR2_SIZE_MAX		256

#define MT7621_CHIP_NAME0		0x3637544D
#define MT7621_CHIP_NAME1		0x20203132

#define MIPS_GIC_IRQ_BASE           (MIPS_CPU_IRQ_BASE + 8)

#define MT7621_GPIO_BASE		0x1E000600

#define MT7621_GPIO_I2C_MODE		(0x1 << 2)
#define MT7621_GPIO_UART3_MODE		(0x1 << 3)
#define MT7621_GPIO_UART3_MODE_MASK	(0x3 << 3)
#define MT7621_GPIO_UART2_MODE		(0x1 << 5)
#define MT7621_GPIO_UART2_MODE_MASK	(0x3 << 5)
#define MT7621_GPIO_JTAG_MODE		(0x1 << 7)
#define MT7621_GPIO_WDT_MODE		(0x1 << 8)
#define MT7621_GPIO_WDT_MODE_MASK	(0x3 << 8)

extern __iomem void *rt_sysc_membase;
extern __iomem void *rt_memc_membase;

static inline void rt_sysc_w32(u32 val, unsigned reg)
{
	__raw_writel(val, rt_sysc_membase + reg);
}

static inline u32 rt_sysc_r32(unsigned reg)
{
	return __raw_readl(rt_sysc_membase + reg);
}

static inline void rt_memc_w32(u32 val, unsigned reg)
{
	__raw_writel(val, rt_memc_membase + reg);
}

static inline u32 rt_memc_r32(unsigned reg)
{
	return __raw_readl(rt_memc_membase + reg);
}

static inline u32 rt_reg_r32(unsigned reg)
{
	return (*((volatile u32 *) (KSEG1ADDR(reg))));
}

static inline void rt_reg_w32(u32 val, unsigned reg)
{
	(*((volatile u32 *) (KSEG1ADDR(reg)))) = val;
}

void mt7621_gpio_init(u32 mode);

#endif
